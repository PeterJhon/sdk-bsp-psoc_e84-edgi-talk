
/*
 * Copyright (c) 2006-2018 RT-Thread Development Team. All rights reserved.
 * License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "mbedtls/certs.h"

const char mbedtls_root_certificate[] =
    "-----BEGIN CERTIFICATE-----\r\n" \
    "MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\r\n" \
    "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\r\n" \
    "DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\r\n" \
    "PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\r\n" \
    "Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\r\n" \
    "AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\r\n" \
    "rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\r\n" \
    "OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\r\n" \
    "xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\r\n" \
    "7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\r\n" \
    "aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\r\n" \
    "HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\r\n" \
    "SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\r\n" \
    "ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\r\n" \
    "AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz\r\n" \
    "R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\r\n" \
    "JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\r\n" \
    "Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ\r\n" \
    "-----END CERTIFICATE-----\r\n" \
    "-----BEGIN CERTIFICATE-----\r\n" \
    "MIIGYDCCBUigAwIBAgIQDxmd2dKm9/1nJckzl5uhdTANBgkqhkiG9w0BAQsFADBE\r\n" \
    "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMR4wHAYDVQQDExVH\r\n" \
    "ZW9UcnVzdCBSU0EgQ04gQ0EgRzIwHhcNMjQxMTA1MDAwMDAwWhcNMjUxMTA4MjM1\r\n" \
    "OTU5WjB/MQswCQYDVQQGEwJDTjESMBAGA1UECAwJ5bm/5Lic55yBMRIwEAYDVQQH\r\n" \
    "DAnmt7HlnLPluIIxLTArBgNVBAoMJOa3seWcs+WNgeaWueiejea1t+enkeaKgOac\r\n" \
    "iemZkOWFrOWPuDEZMBcGA1UEAxMQYXBpLnRlbmNsYXNzLm5ldDCCASIwDQYJKoZI\r\n" \
    "hvcNAQEBBQADggEPADCCAQoCggEBAJqVebZci8IunZlKvRqTeXRdJfAr+aSksbxC\r\n" \
    "T8ijnagY7W6hR5n/21nLUAVzJhjKm86S6SfgXUPVP0AokzqpQvlKlv0cnn3jobIu\r\n" \
    "dZNFp5U43+h8gSFIYmUd4GMqvSjUY20aTdwAX9b1VpuHX94vspPWXGEVPTaAe0uJ\r\n" \
    "XNQXTVmqGXw7BPEPAeHzEHs+dvnpZ/Yhj8SxKYNXYlTGEigAfN7KhOMH1b2WOOtk\r\n" \
    "AqCKiDEyAQAuH63Msq3xI8ogGFz4MTwhIEFwm+eYq/c8iE2OhxhWbiHvU5SO62E6\r\n" \
    "m0kY/2XTkrVgIImM9c4rqCURGy8HYaQzd76p23uEkOXVft7nBwcCAwEAAaOCAxEw\r\n" \
    "ggMNMB8GA1UdIwQYMBaAFCRvkT+Jh4cOMsJAGN/FTOtPyEkyMB0GA1UdDgQWBBRR\r\n" \
    "/eAxc0mjN/HlTqfgRC8sWD8HwDAbBgNVHREEFDASghBhcGkudGVuY2xhc3MubmV0\r\n" \
    "MD4GA1UdIAQ3MDUwMwYGZ4EMAQICMCkwJwYIKwYBBQUHAgEWG2h0dHA6Ly93d3cu\r\n" \
    "ZGlnaWNlcnQuY29tL0NQUzAOBgNVHQ8BAf8EBAMCBaAwHQYDVR0lBBYwFAYIKwYB\r\n" \
    "BQUHAwEGCCsGAQUFBwMCMD0GA1UdHwQ2MDQwMqAwoC6GLGh0dHA6Ly9jcmwuZGln\r\n" \
    "aWNlcnQuY24vR2VvVHJ1c3RSU0FDTkNBRzIuY3JsMHEGCCsGAQUFBwEBBGUwYzAj\r\n" \
    "BggrBgEFBQcwAYYXaHR0cDovL29jc3AuZGlnaWNlcnQuY24wPAYIKwYBBQUHMAKG\r\n" \
    "MGh0dHA6Ly9jYWNlcnRzLmRpZ2ljZXJ0LmNuL0dlb1RydXN0UlNBQ05DQUcyLmNy\r\n" \
    "dDAMBgNVHRMBAf8EAjAAMIIBfQYKKwYBBAHWeQIEAgSCAW0EggFpAWcAdgAS8U40\r\n" \
    "vVNyTIQGGcOPP3oT+Oe1YoeInG0wBYTr5YYmOgAAAZL5okt0AAAEAwBHMEUCIBe9\r\n" \
    "ayTEaI9+dC0ZQMyTt0BIy5vRHfLjv9jpHL57iykxAiEA2p9yTyH4aEbazIRQ0qYY\r\n" \
    "BOZwJtu+XxQOSK4tJRBB1jUAdgB9WR4S4XgqexxhZ3xe/fjQh1wUoE6VnrkDL9kO\r\n" \
    "jC55uAAAAZL5oksrAAAEAwBHMEUCIQC8AknPmIq7O6tYsyppl6JV5RJEqTgSvWx4\r\n" \
    "ns8wnjZruwIgIuf0XYPM8eHvXpRn7UPynJnRaiFbNuUJ54ETaH4Fw10AdQDm0jFj\r\n" \
    "QHeMwRBBBtdxuc7B0kD2loSG+7qHMh39HjeOUAAAAZL5oktQAAAEAwBGMEQCIDmo\r\n" \
    "uejn6L/3z7IRLzZRqk4sVgfYDVGZI08YFurlgClqAiAP0DixCkryP7Q6FkwKwYni\r\n" \
    "IBDWNiwQvcPsz+G+2wUANTANBgkqhkiG9w0BAQsFAAOCAQEAlHZ4zA8mRNSfkw8j\r\n" \
    "1u0O9Z99P+VvGxRt6wfFPwiFGl2sHQzRFXpfpEfgVJ3czIuiRRW5G2D5SAgYcteX\r\n" \
    "2Xk7MLjJSdNlstvuOlZ5UgKk2SNS3UT/EL7Qry5hH9zoLWtJ/gES3obQ3roayrfw\r\n" \
    "UyzfIpg+SKOUxCjkhtj88PWBWP7ZodtXI6V/RASJGDauptUGiF3QLSZLw3Ibk1UE\r\n" \
    "RBlV4PLK5r0WU2rpXYcX0D8pBh3stFnbgyeed3opXjpvojdLb+rOZDLOs/Ht/StJ\r\n" \
    "7NvImQb0pysy/FFzQ9z3S6eGeJ7b1x52hUcdDddC00TP+o6VcOUBz6PoksgGTynZ\r\n" \
    "zK8mkw==\r\n" \
    "-----END CERTIFICATE-----\r\n" \
    "-----BEGIN CERTIFICATE-----\r\n" \
    "MIIFDzCCA/egAwIBAgIQCxNitu5qnT6WiTDxbiB9OTANBgkqhkiG9w0BAQsFADBh\r\n" \
    "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n" \
    "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\r\n" \
    "QTAeFw0yMDAzMDQxMjA0NDBaFw0zMDAzMDQxMjA0NDBaMEQxCzAJBgNVBAYTAlVT\r\n" \
    "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxHjAcBgNVBAMTFUdlb1RydXN0IFJTQSBD\r\n" \
    "TiBDQSBHMjCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANA1OZJJtZUI\r\n" \
    "7zj4qFHT79g+Otks4TEfmUEDhrNKBEEjb/i29GBfnpvFdT36azCg2VODJRSjIzFn\r\n" \
    "4qADcc84EmfKiDEM97HFsQPp9RRkqxH5cB51EU2eBE9Ua95x+wQp/KSdCqITCQ/v\r\n" \
    "yvm3J4Upjl0wlW8wRCPCWcYw3pKClGRkNzVtI1KXnfpn7fG3N84n7wlBb9IGKJFa\r\n" \
    "c/6+hxvZx2qnfLsxdIKR0Q/biGoU6Z8Iy/R/p7GoPO8vamV090+QHEL5AdSzKtEh\r\n" \
    "U9vdvcuWjjLxVnaJLfj/6WoGZj8UWn3zFbEoTVaAfp2xqdzW7yRvi2r148m9ev7l\r\n" \
    "jDqHo8UX69sCAwEAAaOCAd4wggHaMB0GA1UdDgQWBBQkb5E/iYeHDjLCQBjfxUzr\r\n" \
    "T8hJMjAfBgNVHSMEGDAWgBQD3lA1VtFMu2bwo+IbG8OXsj3RVTAOBgNVHQ8BAf8E\r\n" \
    "BAMCAYYwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMBIGA1UdEwEB/wQI\r\n" \
    "MAYBAf8CAQAwMwYIKwYBBQUHAQEEJzAlMCMGCCsGAQUFBzABhhdodHRwOi8vb2Nz\r\n" \
    "cC5kaWdpY2VydC5jbjBABgNVHR8EOTA3MDWgM6Axhi9odHRwOi8vY3JsLmRpZ2lj\r\n" \
    "ZXJ0LmNuL0RpZ2lDZXJ0R2xvYmFsUm9vdENBLmNybDCB3QYDVR0gBIHVMIHSMIHF\r\n" \
    "BglghkgBhv1sAQEwgbcwKAYIKwYBBQUHAgEWHGh0dHBzOi8vd3d3LmRpZ2ljZXJ0\r\n" \
    "LmNvbS9DUFMwgYoGCCsGAQUFBwICMH4MfEFueSB1c2Ugb2YgdGhpcyBDZXJ0aWZp\r\n" \
    "Y2F0ZSBjb25zdGl0dXRlcyBhY2NlcHRhbmNlIG9mIHRoZSBSZWx5aW5nIFBhcnR5\r\n" \
    "IEFncmVlbWVudCBsb2NhdGVkIGF0IGh0dHBzOi8vd3d3LmRpZ2ljZXJ0LmNvbS9y\r\n" \
    "cGEtdWEwCAYGZ4EMAQICMA0GCSqGSIb3DQEBCwUAA4IBAQCzkcXq0TN0oSn4UeXp\r\n" \
    "FBW7U8zrHBIhH9MXHNBp+Yy/yN19133UY05uuHXHaU2Uv0hxefckjPdkaX7ARso+\r\n" \
    "O3Ar6nf7YfBwCqSpqsNckKT7KKtf3Ot95wYFpKDa64jcRUfxzRWnmq12IVzczqHI\r\n" \
    "sIvUZQINw/UHSQcWekdUnMg58bQSHyTjwkj9jcX2RURxaVZkr15wxo/Z3Ydo2PVK\r\n" \
    "3afEr0/vcuFvE7QeGXiI2DJdVt3JefatZ3rj4VTW2aUZwHGUiWWIUudBfQKR0JEp\r\n" \
    "lJ8MFaKDh4/A2VEJnXILu1iwvc1m3jCaPuzZKdoHM/1234bznJI2aAfhfIhoHw90\r\n" \
    "tPO+\r\n" \
    "-----END CERTIFICATE-----\r\n" \
    "-----BEGIN CERTIFICATE-----\r\n" \
    "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\r\n" \
    "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n" \
    "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\r\n" \
    "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\r\n" \
    "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\r\n" \
    "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\r\n" \
    "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\r\n" \
    "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\r\n" \
    "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\r\n" \
    "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\r\n" \
    "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\r\n" \
    "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\r\n" \
    "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\r\n" \
    "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\r\n" \
    "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\r\n" \
    "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\r\n" \
    "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\r\n" \
    "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\r\n" \
    "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\r\n" \
    "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\r\n" \
    "-----END CERTIFICATE-----\r\n" \

    ;

const size_t mbedtls_root_certificate_len = sizeof(mbedtls_root_certificate);

