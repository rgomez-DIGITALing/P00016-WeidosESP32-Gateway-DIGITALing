#pragma once

#include <Arduino.h>
#include <az_iot.h>
#include "AzureIoT_definitions.h"
/* --- Other Interface functions required by Azure IoT --- */



/*
 * See the documentation of `hmac_sha256_encryption_function_t` in AzureIoT.h for details.
 */
int eccx08_hmac_sha256(const uint8_t* key, size_t key_length, const uint8_t* payload, size_t payload_length, uint8_t* signed_payload, size_t signed_payload_size);

/*
 * See the documentation of `base64_decode_function_t` in AzureIoT.h for details.
 */
int base64_decode(
    uint8_t* data,
    size_t data_length,
    uint8_t* decoded,
    size_t decoded_size,
    size_t* decoded_length);

/*
 * See the documentation of `base64_encode_function_t` in AzureIoT.h for details.
 */
int base64_encode(
    uint8_t* data,
    size_t data_length,
    uint8_t* encoded,
    size_t encoded_size,
    size_t* encoded_length);

/*
 * See the documentation of `properties_update_completed_t` in AzureIoT.h for details.
 */
void on_properties_update_completed(uint32_t request_id, az_iot_status status_code);


/*
 * See the documentation of `properties_received_t` in AzureIoT.h for details.
 */
void on_properties_received(az_span properties);

/*
 * See the documentation of `command_request_received_t` in AzureIoT.h for details.
 */
void on_command_request_received(command_request_t command);


