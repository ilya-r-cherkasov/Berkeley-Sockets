//
//  String.swift
//  SocketClient
//
//  Created by Ilya Cherkasov on 17.11.2022.
//

extension String {

    var toCString: UnsafeMutablePointer<Int8> {
        let count = utf8.count + 1
        let result = UnsafeMutablePointer<Int8>.allocate(capacity: count)
        withCString { (baseAddress) in
            result.initialize(from: baseAddress, count: count)
        }
        return result
    }

}
