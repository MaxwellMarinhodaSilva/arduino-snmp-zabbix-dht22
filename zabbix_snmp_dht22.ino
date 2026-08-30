#include <SPI.h>
#include <Ethernet.h>
#include <Agentuino.h>
#include <DHT.h>

// Configuração do sensor DHT22
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Configuração do Ethernet Shield W5100
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 100); // IP fixo do seu Arduino

// OIDs personalizados para Temperatura e Umidade
const char oid_temp[] = "1.3.6.1.4.1.12345.1.0";
const char oid_hum[]  = "1.3.6.1.4.1.12345.2.0";

// Variáveis para guardar a última leitura e não travar o SNMP
float lastTemp = 0.0;
float lastHum = 0.0;
unsigned long lastReadTime = 0;

// Função chamada automaticamente quando o Zabbix faz um GET SNMP
void pduReceived() {
  SNMP_PDU pdu;
  api_status status = Agentuino.requestPdu(&pdu);
  
  if (status == SNMP_API_STAT_SUCCESS) {
    if (pdu.type == SNMP_PDU_GET) {
      pdu.type = SNMP_PDU_RESPONSE;
      pdu.error = SNMP_ERR_NO_ERROR;

      // Zabbix pediu Temperatura
      if (strcmp(pdu.OID.data, oid_temp) == 0) {
        char tempStr[10];
        dtostrf(lastTemp, 4, 2, tempStr); // Converte float para string
        status = pdu.VALUE.encode(SNMP_SYNTAX_OCTETS, tempStr);
      }
      // Zabbix pediu Umidade
      else if (strcmp(pdu.OID.data, oid_hum) == 0) {
        char humStr[10];
        dtostrf(lastHum, 4, 2, humStr); // Converte float para string
        status = pdu.VALUE.encode(SNMP_SYNTAX_OCTETS, humStr);
      }
      // OID desconhecido
      else {
        pdu.error = SNMP_ERR_NO_SUCH_NAME;
      }
      
      Agentuino.responsePdu(&pdu);
    }
  }
  Agentuino.freePdu(&pdu);
}

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Inicia a rede
  Ethernet.begin(mac, ip);
  
  // Inicia o agente SNMP
  api_status status = Agentuino.begin();
  if (status == SNMP_API_STAT_SUCCESS) {
    // Configura a função que vai responder ao Zabbix
    Agentuino.onPduReceive(pduReceived);
    Serial.println("Agente SNMP Iniciado.");
    Serial.print("IP: ");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.println("Falha ao iniciar o SNMP.");
  }
}

void loop() {
  // Mantém o SNMP escutando requisições do Zabbix (NÃO PODE TER DELAY AQUI)
  Agentuino.listen();

  // Lê o DHT22 a cada 5 segundos para manter o valor atualizado na memória
  // Fazer a leitura diretamente no callback atrasa a resposta SNMP e causa timeout
  if (millis() - lastReadTime > 5000) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    
    if (!isnan(t) && !isnan(h)) {
      lastTemp = t;
      lastHum = h;
    }
    lastReadTime = millis();
  }
}
