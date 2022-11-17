//
//  main.swift
//  SocketClient
//
//  Created by Ilya Cherkasov on 16.11.2022.
//

func makeCString(from str: String) -> UnsafeMutablePointer<Int8> {
    let count = str.utf8.count + 1
    let result = UnsafeMutablePointer<Int8>.allocate(capacity: count)
    str.withCString { (baseAddress) in
        // func initialize(from: UnsafePointer<Pointee>, count: Int)
        result.initialize(from: baseAddress, count: count)
    }
    return result
}

//make_udp_request()

let host = "www.google.com"
send_http_request(makeCString(from: host), 80)
