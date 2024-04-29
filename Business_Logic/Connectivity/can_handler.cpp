#include "can_handler.h"


#define CANID_29_BIT 0x3FFFFFFFUL
#define CANID_RAW_DATA_BIT 0x80000000UL

using namespace std;

mutex CanDataHandler::m_build_mutex;
shared_ptr<CanDataHandler> CanDataHandler::m_ptr_instance(nullptr);

static pthread_t can_data_read_thread;
//static pthread_t hmi_save_thread;
static queue<pair<can_msg_rx_t*, can_frame*>> g_accepted_can_msgs;
static queue<can_frame> g_msgs_to_send;
static bool ext_threads = false;


static CanDataHandler::UDSDetails uds_can_response_st;

CanDataHandler::CanDataHandler()
    : is_exit(false)
    , m_ptr_msg_holder()
    , m_filter_can_messages()
{
    m_ptr_msg_holder = HmiHandler::getInstance();
    m_ptr_dm_data_holder = J1939DataHandler::getInstance();
}

CanDataHandler::~CanDataHandler()
{
    ext_threads = true;
    is_exit = true;
}

CanDataHandler* CanDataHandler::getInstance()
{
    TRY_BLOCK
        if (!m_ptr_instance)
        {
            lock_guard<mutex> build_locker(m_build_mutex);
            m_ptr_instance = (shared_ptr<CanDataHandler>(new CanDataHandler));
        }
        return m_ptr_instance.get();
    CATCH_BLOCK

}

void* process_can_data_function(void*);

void can_write_data()
{
    TRY_BLOCK
    CanDataHandler* ptr_can_handler_instance = CanDataHandler::getInstance();
    can_msg_rx_t* _ddsettings = reinterpret_cast<can_msg_rx_t*>(ptr_can_handler_instance->get_msg_from_cache(HMIHANDLER_DD_SETTINGS_ID));
    auto _can_fd = ptr_can_handler_instance->can_fd_get();
    can_frame frame_tx;
    frame_tx.can_id = HMIHANDLER_DD_SETTINGS_ID | CAN_EFF_FLAG;
    frame_tx.can_dlc = 8;
    while(!ptr_can_handler_instance->exit_status())
    {
        uint64_t* ptr_data =  _ddsettings->get_data();
        memcpy(&frame_tx.data, ptr_data, sizeof(frame_tx.data));
        write(*_can_fd, &frame_tx, sizeof(can_frame));
        this_thread::sleep_for(1000ms);
    }
    CATCH_BLOCK
}

void* can_read_thread_function(void*)
{
    TRY_BLOCK
    CanDataHandler* ptr_can_handler_instance = CanDataHandler::m_ptr_instance.get();
    while (!ext_threads)
    {
    int frame_rx_nbytes = 0;
    try {
        can_frame can_read_frame_rx;
        frame_rx_nbytes = read(ptr_can_handler_instance->m_can_fd, &can_read_frame_rx, sizeof(can_frame));
        can_read_frame_rx.can_id &= CANID_29_BIT;
        if (frame_rx_nbytes < 0) {
            perror("can raw socket read");
        }

        // paranoid check ...
        if (frame_rx_nbytes < ((int)sizeof(can_frame))) {
            qDebug("Incomplete CAN Frame Error\n");
            fprintf(stderr, "read: incomplete CAN frame\n");
        }
        auto pair_data = make_pair<can_msg_rx_t*, can_frame*>(ptr_can_handler_instance->m_ptr_msg_holder->get_ptr_to_msg(can_read_frame_rx.can_id), &can_read_frame_rx);
        g_accepted_can_msgs.push(pair_data);
        process_can_data_function(nullptr);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    }
    return nullptr;
    CATCH_BLOCK
}

void* process_can_data_function(void*)
{
    TRY_BLOCK
    CanDataHandler* ptr_can_handler_instance= CanDataHandler::m_ptr_instance.get();
//    while (!ext_threads)
//    {
        try
        {
            if (!g_accepted_can_msgs.empty())
            {
                lock_guard<mutex> lock_peek_queue(ptr_can_handler_instance->m_queue_access_mutex);
                auto queued_msg = g_accepted_can_msgs.front();

                if(queued_msg.second->can_id == HMIHANDLER_DD_SETTINGS_ID)
                {
                    g_accepted_can_msgs.pop();
                    return nullptr;
                }

                if(likely(queued_msg.first))
                {
                    uint64_t msg = 0;
                    memcpy(&msg, queued_msg.second->data, 8 * sizeof(char));
                    ptr_can_handler_instance->m_ptr_msg_holder->add_new_data(queued_msg.second->can_id, CAN_MESSAGE_STATE_OK, msg);
                }
                else if(g_DM1_pairs.find(queued_msg.second->can_id) != g_DM1_pairs.end())
                {
                    ptr_can_handler_instance->m_ptr_dm_data_holder->set_total_frames
                            (g_DM1_pairs.find(queued_msg.second->can_id)->second, (queued_msg.second->data[3]));
                }
                else
                {
                    auto ptr_DM_msg = ptr_can_handler_instance->m_ptr_dm_data_holder->get_ptr_to_msg(queued_msg.second->can_id);
                    if (ptr_DM_msg)
                    {
                        ptr_DM_msg->frame_count++;

                        if(ptr_DM_msg->frame_count == queued_msg.second->data[0])
                        {
                            if (ptr_DM_msg->frame_count <= ptr_DM_msg->no_of_frames_total)
                                for (auto i = 1; i < CAN_MAX_DLEN; ++i)
                                    ptr_DM_msg->j1939_raw_data[ptr_DM_msg->index_iterator++] = queued_msg.second->data[i];

                            if (ptr_DM_msg->frame_count == ptr_DM_msg->no_of_frames_total)
                                ptr_can_handler_instance->m_ptr_dm_data_holder->update_dm1_details(queued_msg.second->can_id);
                        }
                    }
                }

                g_accepted_can_msgs.pop();
//            ptr_can_handler_instance->m_ptr_subject->notify();
            }
            else
                this_thread::yield();
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
//    }
    return nullptr;
    CATCH_BLOCK
}

int* CanDataHandler::can_fd_get()
{
    TRY_BLOCK
    return &m_can_fd;
    CATCH_BLOCK
}

bool CanDataHandler::send_can_msg(can_frame _can_msg)
{
    TRY_BLOCK
    //TODO: try catch scenario
    g_msgs_to_send.push(_can_msg);
    return true;
    CATCH_BLOCK
}

CanDataHandler::UDSDetails* CanDataHandler::get_uds_can_response()
{
    TRY_BLOCK
    return &uds_can_response_st;
    CATCH_BLOCK
}


int CanDataHandler::can_init()
{
    TRY_BLOCK
    int ret_status = STATUS_OK;
    sockaddr_can soc_addr;
    ifreq ifr;

    memset(&soc_addr, 0, sizeof(soc_addr));
    memset(&ifr, 0, sizeof(ifr));

    strcpy(ifr.ifr_name, "can0");//*"vcan0"; */

    if ((m_can_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) == -1) {
        perror("Error while opening socket\n");
        ret_status = STATUS_SOCKET_CREATION_FAILED;
    }

    ioctl(m_can_fd, SIOCGIFINDEX, &ifr);

    soc_addr.can_family = AF_CAN;
    soc_addr.can_ifindex = ifr.ifr_ifindex;

    string ifname(ifr.ifr_name);
    qDebug("%s at index %d\n", ifname.c_str(), ifr.ifr_ifindex);

    if (bind(m_can_fd, reinterpret_cast<sockaddr*>(&soc_addr), sizeof(soc_addr)) == -1) {
        perror("Error in socket bind");
        ret_status = STATUS_BINDING_PROCESS_FAILED;
    }

    this->update_filter_can_messages_array();
    can_err_mask_t err_mask =
            ( CAN_ERR_TX_TIMEOUT   /* TX timeout (by netdevice driver) */
            | CAN_ERR_LOSTARB      /* lost arbitration    / data[0]    */
            | CAN_ERR_CRTL         /* controller problems / data[1]    */
            | CAN_ERR_PROT         /* protocol violations / data[2..3] */
            | CAN_ERR_TRX          /* transceiver status  / data[4]    */
            | CAN_ERR_ACK           /* received no ACK on transmission */
            | CAN_ERR_BUSOFF        /* bus off */
            //CAN_ERR_BUSERROR      /* bus error (may flood!) */
            | CAN_ERR_RESTARTED     /* controller restarted */
            );
    setsockopt(m_can_fd, SOL_CAN_RAW, CAN_RAW_ERR_FILTER, &err_mask, sizeof(err_mask));
    setsockopt(m_can_fd, SOL_CAN_RAW, CAN_RAW_FILTER, &m_filter_can_messages, sizeof (m_filter_can_messages));

    pthread_create(&can_data_read_thread, NULL, can_read_thread_function, NULL);
//    pthread_create(&hmi_save_thread, NULL, process_can_data_function, NULL);

    return ret_status;
    CATCH_BLOCK
}

void CanDataHandler::update_filter_can_messages_array()
{
    TRY_BLOCK
    size_t i;

    for (i = 0; i < g_CAN_msg_ids.size(); i++)
    {
        m_filter_can_messages[i].can_id = g_CAN_msg_ids[i].first;
        m_filter_can_messages[i].can_mask = (CAN_EFF_MASK);
    }

    for (auto it : g_DM1_pairs)
    {
        m_filter_can_messages[i].can_id = it.first;
        m_filter_can_messages[i++].can_mask = (CAN_EFF_MASK);
        m_filter_can_messages[i].can_id = it.second;
        m_filter_can_messages[i++].can_mask = (CAN_EFF_MASK);
    }
    CATCH_BLOCK
}
