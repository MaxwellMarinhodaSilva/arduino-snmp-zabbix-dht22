# 🌡️ Monitoramento de Temperatura e Umidade via SNMP (Arduino + Zabbix)

Solução de baixo custo para coleta e monitoramento de temperatura e umidade em ambientes de TI, utilizando Arduino + Ethernet Shield W5100 + DHT22 e integração com Zabbix via SNMP.

---

### 🚀 Funcionalidades

- **Agente SNMP Naitvo:** Responde a requisições GET diretamente do servidor Zabbix.
- **Leitura Assíncrona:** Leitura do sensor DHT22 a cada 5 segundos salva em memória para evitar *timeout* e congelamento das requisições SNMP.
- **Baixo Custo:** Solução acessível para monitoramento de salas de servidores, Data Centers e Racks de TI.

---

### 🛠️ Hardware Necessário

- Arduino (Uno ou Mega)
- Ethernet Shield W5100
- Sensor de Temperatura e Umidade DHT22
- Cabo de Rede RJ45

---

### 📋 Mapeamento das OIDs SNMP

| Métrica | OID Personalizada | Tipo de Dado |
| :--- | :--- | :--- |
| **Temperatura (°C)** | `1.3.6.1.4.1.12345.1.0` | OCTET STRING |
| **Umidade (%)** | `1.3.6.1.4.1.12345.2.0` | OCTET STRING |

---

### 📦 Bibliotecas Requeridas

Antes de compilar o código na IDE do Arduino, instale as seguintes bibliotecas:
- `Ethernet.h` (Inclusa na IDE)
- `SPI.h` (Inclusa na IDE)
- `DHT sensor library` (por Adafruit)
- `Agentuino.h` (Biblioteca para agente SNMP no Arduino)

---

### ⚙️ Como Configurar no Zabbix

1. Crie um novo Host no Zabbix com a interface **SNMP**.
2. Defina o endereço IP estático configurado no código (Padrão: `192.168.0.100`).
3. Adicione um item de monitoramento com a OID referente à Temperatura ou Umidade.
4. Defina o tipo de informação como **Texto** ou use um pré-processamento **Trim** para converter o valor em Numérico (Float).
