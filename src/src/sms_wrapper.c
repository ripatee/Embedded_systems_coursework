#include <stdio.h>
#include <string.h>

#include <zephyr/logging/log.h>
#include <modem/sms.h>

LOG_MODULE_REGISTER(SMS_WRAPPER, LOG_LEVEL_INF);

BUILD_ASSERT(sizeof(CONFIG_SMS_RECEIVER_NUMBER) > 1, "SMS receiver number is empty");

/* Private functions */
static void sms_callback(struct sms_data *const data, void *context)
{
    if (data == NULL)
    {
        LOG_ERR("SMS data is NULL");
        return;
    }

    switch (data->type)
    {
    case SMS_TYPE_DELIVER:

        struct sms_deliver_header *header = &data->header.deliver;

        LOG_INF("\nReceived SMS message.");
        LOG_INF("\t Time:    %02d-%02d-%02d %02d:%02d:%02d",
            header->time.year,
            header->time.month,
            header->time.day,
            header->time.hour,
            header->time.minute,
            header->time.second);

        LOG_INF("\tText: '%s'", data->payload);
        LOG_INF("\tLenght: %d", data->payload_len);

        if (header->app_port.present) {
            LOG_INF("\tApplication port addressing scheme: dest_port=%d, src_port=%d",
                header->app_port.dest_port,
                header->app_port.src_port);
        }
        if (header->concatenated.present) {
            LOG_INF("\tConcatenated short message: ref_number=%d, msg %d/%d",
                header->concatenated.ref_number,
                header->concatenated.seq_number,
                header->concatenated.total_msgs);
        }
        break;
    case SMS_TYPE_STATUS_REPORT:
        LOG_INF("SMS status repor received");
        break;
    default:
        LOG_INF("SMS protocol message with unkown type received"); 
    }
}

/* Public functions */
int sms_init()
{
    return sms_register_listener(sms_callback, NULL);
}

int sms_send_temp_alert(double temperature)
{
    int ret;
    char msg[SMS_MAX_PAYLOAD_LEN_CHARS];

    LOG_INF("Sending temperature warning");

    snprintfcb(msg, SMS_MAX_PAYLOAD_LEN_CHARS, 
               "Temperature alert has triggered. Temperature: %.2fC. -IoT-sulari",
               temperature);

    LOG_DBG("Sending SMS: number='%s' \nmsg='%s'",
             CONFIG_SMS_RECEIVER_NUMBER, msg);

    ret = sms_send_text(CONFIG_SMS_RECEIVER_NUMBER, msg);
    if (ret)
    {
        LOG_ERR("Sending SMS failed with error: %d", ret);
    }
    return ret;
}