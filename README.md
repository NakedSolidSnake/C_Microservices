![Microservices](https://www.xenonstack.com/images/insights/xenonstack-what-are-microservices.png)

# Microservices
Após diversas discussões sobre o que seria a vir microserviços. Aqui vai algumas conclusões sobre esse
padrão arquitetural
Um microserviço não é somente uma fragmentação de tarefas providas pelo servidor, mas sim um serviço isolado
que contém sua própria interface pública de comunicação, ou seja, é possível ser conectar diretamente ao 
serviço e consumir seus serviços.

# API Gateway

API Gateway é uma padrão que centraliza todas as interfaces de comunicação relativo aos serviços
disponíveis em uma única interface pública, sendo assim tendo como responsabilidade de rotear os
endpoints para a respectiva interface pública que contém o serviço.

# Caso de Uso

Para exemplicar o padrão, foi criado um projeto onde possui uma aplicação Gateway e Serviço.

## Gateway 

A aplicação Gateway é responsável por centralizar todas as requisições vinda do cliente, e rotear para o endpoint correspondente
através de leitura de uma arquivo criado pelos serviços.

## Service

A aplicação Service é responsável por enviar mensagens conforme são cadastradas por passagem de paramêtros. Cada serviço criado
registra sua porta e seu endpoint em um arquivo informando que está disponível.

# Uso
## Build
```bash
$ cd c_microservices
$ mkdir build
$ cd build
$ cmake ..
$ make
```


## Usando o Gateway
**./gateway <port>**

## Usando o Service
**./service <port> <endpoint> <message>**

Iniciamos o gateway e os serviços
## Exemplo de uso
```bash
./gateway 1111 &
./service 1112 /service1 'Hello World'&
./service 1113 /service2 'Hallo Welt'&
./service 1114 /service3 'salve Orbis Terrarum'&
./service 1115 /service4 'Bonjour le monde'&
```

Com o netstat podemos ver os serviços funcionando

```bash
$ netstat -lvpu | egrep "gateway|service" 

udp        0      0 0.0.0.0:1111            0.0.0.0:*                           25144/./gateway     
udp        0      0 0.0.0.0:1112            0.0.0.0:*                           25365/./service     
udp        0      0 0.0.0.0:1113            0.0.0.0:*                           25440/./service     
udp        0      0 0.0.0.0:1114            0.0.0.0:*                           25485/./service     
udp        0      0 0.0.0.0:1115            0.0.0.0:*                           25559/./service  
```

Conectamos no gateway e realizamos as requisições

```bash
$ nc -u localhost 1111

/service1
Service on port 1112. : Message: Hello World
/service2
Service on port 1113. : Message: Hallo Welt
/service3
Service on port 1114. : Message: salve Orbis Terrarum
/service4
Service on port 1115. : Message: Bonjour le monde

```

Porém podemos nos conectar diretamente no próprio serviço

```bash
$ nc -u localhost 1112
Service on port 1112. : Message: Hello World
```

# Conclusão 
Este material apresenta a conclusão do autor, que no entendimento do mesmo, isso se caracteriza um microserviço.