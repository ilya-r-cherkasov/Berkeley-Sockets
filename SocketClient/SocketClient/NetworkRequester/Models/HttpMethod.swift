//
//  HttpMethod.swift
//  SocketClient
//
//  Created by Ilya Cherkasov on 17.11.2022.
//

enum HttpMethod: String {
    case get

    var toRequest: String {
        rawValue.uppercased()
    }
}
