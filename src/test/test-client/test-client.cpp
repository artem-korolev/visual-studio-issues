/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "greenlight.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using GreenLight::SignUpForm;
using GreenLight::Session;
using GreenLight::LoginService;

class TestClient {
public:
    TestClient(std::shared_ptr<Channel> channel)
        : stub_(LoginService::NewStub(channel)) {}

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    std::string signUp(const SignUpForm& signupForm) {
        // Container for the data we expect from the server.
        Session reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC.
        Status status = stub_->SignUp(&context, signupForm, &reply);

        // Act upon its status.
        if (status.ok()) {
            return reply.session();
        }
        else {
            std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<LoginService::Stub> stub_;
};

int main(int argc, char** argv) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    TestClient greeter(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()));

    // Prepare data to be send to server
    SignUpForm signupForm;
    signupForm.set_email("test@test.com");
    signupForm.set_firstname("Test");
    signupForm.set_firstname("Testovich");
    signupForm.set_password("test");

    int messageCounter = 0;
    while (true) {
        std::string reply = greeter.signUp(signupForm);
        if (messageCounter++ % 1000 == 0) {
            std::cout << "Greeter received: (" << messageCounter << "): " << reply << std::endl;
        }
    }

    return 0;
}


// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
