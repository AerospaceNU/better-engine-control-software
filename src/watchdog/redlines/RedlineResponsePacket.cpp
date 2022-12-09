//
// Created by kevin on 12/8/2022.
//

#include "RedlineResponsePacket.h"
#include <utility>

RedlineResponsePacket::RedlineResponsePacket(ECSRedLineResponse response_, std::string redlineName_):
    response(response_),
    redlineName(std::move(redlineName_))
{}
