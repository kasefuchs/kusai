#include "TextChainService.hpp"

#include <google/protobuf/empty.pb.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>

#include <cstdint>

#include "service.pb.h"

grpc::Status TextChainService::Train(grpc::ServerContext* context, const service::TrainRequest* request,
                                     google::protobuf::Empty* response) {
  chain_.train({request->sequences().begin(), request->sequences().end()});

  return grpc::Status::OK;
}

grpc::Status TextChainService::NextToken(grpc::ServerContext* context, const service::NextTokenRequest* request,
                                         service::NextTokenResponse* response) {
  if (const auto text = chain_.nextToken(request->context()); text.has_value()) {
    response->set_token(*text);
    return grpc::Status::OK;
  }

  return grpc::Status::CANCELLED;
}

grpc::Status TextChainService::GenerateTokens(grpc::ServerContext* context,
                                              const service::GenerateTokensRequest* request,
                                              service::GenerateTokensResponse* response) {
  const auto limit = request->has_limit() ? request->limit() : INT8_MAX;

  const auto text = chain_.generateTokens(request->context(), limit, request->break_value());
  response->set_text(text);

  return grpc::Status::OK;
}
