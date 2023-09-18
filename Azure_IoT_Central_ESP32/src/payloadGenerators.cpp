#include "payloadGenerators.h"
#include "classes/EM750/EM750.h"
#include <LogModule.h>
#include "classes/WeidosESP32Class/WeidosESP32Class.h"

#include <az_core.h>
#include <az_iot.h>

#define EXIT_IF_TRUE(condition, retcode, message, ...) \
  do                                                   \
  {                                                    \
    if (condition)                                     \
    {                                                  \
      LogError(message, ##__VA_ARGS__);                \
      return retcode;                                  \
    }                                                  \
  } while (0)

#define EXIT_IF_AZ_FAILED(azresult, retcode, message, ...) \
  EXIT_IF_TRUE(az_result_failed(azresult), retcode, message, ##__VA_ARGS__)

static const uint8_t null_terminator = '\0';


/* --- Function Checks and Returns --- */
#define RESULT_OK 0
#define RESULT_ERROR __LINE__

#define DOUBLE_DECIMAL_PLACE_DIGITS 2
#define TRIPLE_DECIMAL_PLACE_DIGITS 3

int em750_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, energyMeterManagerData_t& emData){

    az_json_writer jw;
    az_result rc;
    az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
    az_span json_span;

    unsigned long timestamp = emData.timestamp;
    int comState = emData.data.comState;
    float* data = emData.data.data;

    rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

    rc = az_json_writer_append_begin_object(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");


  //########################              ENERGY METER TELEMETRY           #########################
  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_VOLTAGE_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[VOLTAGE_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1N property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_VOLTAGE_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[VOLTAGE_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_VOLTAGE_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[VOLTAGE_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_AVG_VOLTAGE_LN));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgVoltageLN property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[AVG_VOLTAGE_LN_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgVoltageLN property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_VOLTAGE_L1L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1L2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[VOLTAGE_L1L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1L2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_VOLTAGE_L2L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL2L3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[VOLTAGE_L2L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL2L3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_VOLTAGE_L1L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1L3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[VOLTAGE_L1L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1L3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_AVG_VOLTAGE_LL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgVoltageLL property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[AVG_VOLTAGE_LL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgVoltageLL property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_CURRENT_L1));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL1 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[CURRENT_L1_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL1 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_CURRENT_L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[CURRENT_L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_CURRENT_L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[CURRENT_L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_CURRENT_NEUTRAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentNeutral property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[CURRENT_NEUTRAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentNeutral property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_AVG_CURRENTL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgCurrentL property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[AVG_CURRENTL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgCurrentL property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_CURRENT_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[CURRENT_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REAL_POWER_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REAL_POWER_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REAL_POWER_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REAL_POWER_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REAL_POWER_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REAL_POWER_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REAL_POWER_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REAL_POWER_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_APPARENT_POWER_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[APPARENT_POWER_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_APPARENT_POWER_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[APPARENT_POWER_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_APPARENT_POWER_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[APPARENT_POWER_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_APPARENT_POWER_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[APPARENT_POWER_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REACTIVE_POWER_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REACTIVE_POWER_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REACTIVE_POWER_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REACTIVE_POWER_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REACTIVE_POWER_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REACTIVE_POWER_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REACTIVE_POWER_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REACTIVE_POWER_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_COS_PHI_L1));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL1 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[COS_PHI_L1_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL1 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_COS_PHI_L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[COS_PHI_L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_COS_PHI_L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[COS_PHI_L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_AVG_COS_PHI));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgCosPhi property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[AVG_COS_PHI_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgCosPhi property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_FREQUENCY));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding frequency property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[FREQUENCY_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding frequency property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_ROT_FIELD));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding rotField property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[ROT_FIELD_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding rotField property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REAL_ENERGY_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REAL_ENERGY_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REAL_ENERGY_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REAL_ENERGY_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REAL_ENERGY_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REAL_ENERGY_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REAL_ENERGY_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REAL_ENERGY_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyTotal property value to telemetry payload. ");




  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_APPARENT_ENERGY_L1));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL1 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[APPARENT_ENERGY_L1_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL1 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_APPARENT_ENERGY_L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[APPARENT_ENERGY_L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_APPARENT_ENERGY_L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[APPARENT_ENERGY_L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_APPARENT_ENERGY_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[APPARENT_ENERGY_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L1));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL1 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REACTIVE_ENERGY_L1_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL1 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REACTIVE_ENERGY_L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REACTIVE_ENERGY_L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_REACTIVE_ENERGY_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[REACTIVE_ENERGY_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyTotal property value to telemetry payload. ");




  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_THD_VOLTS_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[THD_VOLTS_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_THD_VOLTS_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[THD_VOLTS_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_THD_VOLTS_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[THD_VOLTS_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_AVG_THD_VOLTS_LN));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[AVG_THD_VOLTS_LN_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgTHDVoltsLN property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_THD_CURRENT_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[THD_CURRENT_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_THD_CURRENT_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[THD_CURRENT_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_THD_CURRENT_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[THD_CURRENT_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_AVG_THD_CURRENT_LN));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgTHDCurrentLN property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[AVG_THD_CURRENT_LN_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgTHDCurrentLN property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_THD_VOLTS_L1L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1L2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[THD_VOLTS_L1L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1L2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_THD_VOLTS_L2L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL2L3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[THD_VOLTS_L2L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL2L3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_THD_VOLTS_L1L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1L3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[THD_VOLTS_L1L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1L3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_AVG_THD_VOLTS_LL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgTHDVoltsLL property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[AVG_THD_VOLTS_LL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgTHDVoltsLL property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_POWER_FACTOR_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[POWER_FACTOR_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_POWER_FACTOR_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[POWER_FACTOR_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_POWER_FACTOR_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[POWER_FACTOR_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_POWER_FACTOR_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[POWER_FACTOR_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorTotal property value to telemetry payload. ");





  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_COM_STATE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, comState, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");

    rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_TIMESTAMP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  rc = az_json_writer_append_int32(&jw, timestamp);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");



  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);
  
  return RESULT_OK;
    
}


int weidosESP32_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, WeidosManagerData_t& weidosData){

      az_json_writer jw;
    az_result rc;
    az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
    az_span json_span;


    rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

    rc = az_json_writer_append_begin_object(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");


  //########################              Weidos ESP32 TELEMETRY           #########################
  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_FREE_HEAP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding freeHeap property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.freeHeap, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding freeHeap property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_HEAP_SIZE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding heapSize property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.heapSize, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding heapSize property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_MAX_ALLOC_HEAP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding maxAllocHeap property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.maxAllocHeap, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding maxAllocHeap property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_MIN_FREE_HEAP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding minFreeHeap property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.minFreeHeap, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding minFreeHeap property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_FREE_PSRAM));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding freePsram property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.freePsram, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding freePsram property value to telemetry payload. ");
  
  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_PSRAM_SIZE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding psramSize property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.psramSize, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding psramSize property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_MAX_ALLOC_PSRAM));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding maxAllocPsram property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.maxAllocPsram, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding maxAllocPsram property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_MIN_FREE_PSRAM));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding minFreePsram property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.minFreePsram, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding minFreePsram property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_SKETCH_SIZE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding sketchSize property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.sketchSize, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding sketchSize property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_INTERNAL_TEMPERATURE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding internalTemperature property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.internalTemperature, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding internalTemperature property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_RUNNING_TIME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding runningTime property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.runningTime, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding runningTime property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_HALL_SENSOR));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding hallSensor property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.hallSensor, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding hallSensor property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(TELEMETRY_PROP_NAME_TIMESTAMP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  rc = az_json_writer_append_int32(&jw, weidosData.timestamp);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");

  


  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);
  
  return RESULT_OK;
}
