#include <modem/nrf_modem_lib.h>
#include <modem/lte_lc.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(LTE, LOG_LEVEL_DBG);

K_SEM_DEFINE(lte_connected, 0, 1);

/* Private functions */

static void lte_handler(const struct lte_lc_evt *const evt)
{
    switch (evt->type)
    {
    case LTE_LC_EVT_NW_REG_STATUS:
        if ((evt->nw_reg_status != LTE_LC_NW_REG_REGISTERED_HOME) &&
            (evt->nw_reg_status != LTE_LC_NW_REG_REGISTERED_ROAMING))
        {
            break;
        }

        LOG_INF("Network registration status: %s",
            evt->nw_reg_status == LTE_LC_NW_REG_REGISTERED_HOME ? 
            "Connected - Home network" : "Connected - Roaming");
        k_sem_give(&lte_connected);
        break;
    case LTE_LC_EVT_RRC_UPDATE:
        LOG_INF("RRC mode: %s", evt->rrc_mode == LTE_LC_RRC_MODE_CONNECTED ? 
                "Connected" : "Idle");
        break;		
    default:
        break;
    }
}

/* Public functions */

int lte_modem_configure(void)
{
    int err;

    LOG_INF("Initializing modem library");

    err = nrf_modem_lib_init();
    if (err) {
		LOG_ERR("Failed to initialize the modem library, error: %d", err);
		return err;
	}

    LOG_INF("Connecting to LTE network");

	err = lte_lc_connect_async(lte_handler);
	if (err) {
		LOG_ERR("Modem could not be configured, error: %d", err);
		return err;
	}

    k_sem_take(&lte_connected, K_FOREVER);
    LOG_INF("Connected to LTE network");

	return 0;
}