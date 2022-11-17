//
//  main.swift
//  SocketClient
//
//  Created by Ilya Cherkasov on 16.11.2022.
//

//https://storage.yandexcloud.net/ilya-cherkasov/simpleJSON

let host = "storage.yandexcloud.net"
let method = "GET /ilya-cherkasov/simpleJSON HTTP/1.1\r\nHost: storage.yandexcloud.net\r\n\r\n"
//TODO: - NEEDS FURTHER REFINEMENT
let path = ""
let port: UInt16 = 80

send_http_request(
    request_params(
        host: host.toCString,
        method: method.toCString,
        path: path.toCString,
        port: port
    )
)
