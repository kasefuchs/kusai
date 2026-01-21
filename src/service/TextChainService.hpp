#pragma once

#include "TextChain.hpp"
#include "service.grpc.pb.h"

class TextChainService : public service::TextChain::Service {
public:
  explicit TextChainService(const TextChain &chain) : chain_(chain) {}

  grpc::Status Train(grpc::ServerContext *context, const service::TrainRequest *request,
                     google::protobuf::Empty *response) override;

  grpc::Status NextToken(grpc::ServerContext *context, const service::NextTokenRequest *request,
                         service::NextTokenResponse *response) override;

  grpc::Status GenerateTokens(grpc::ServerContext *context, const service::GenerateTokensRequest *request,
                              service::GenerateTokensResponse *response) override;

private:
  TextChain chain_;
};
