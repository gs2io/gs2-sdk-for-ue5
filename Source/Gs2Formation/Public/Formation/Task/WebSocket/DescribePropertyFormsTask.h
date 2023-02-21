/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"

#include "Core/Gs2Core.h"
#include "Formation/Request/DescribePropertyFormsRequest.h"
#include "Formation/Result/DescribePropertyFormsResult.h"

namespace Gs2::Formation::Task::WebSocket
{
    class GS2FORMATION_API FDescribePropertyFormsTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribePropertyFormsResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FDescribePropertyFormsRequestPtr Request;
    public:
        explicit FDescribePropertyFormsTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FDescribePropertyFormsRequestPtr Request
        );
        FDescribePropertyFormsTask(
            const FDescribePropertyFormsTask& From
        );
        virtual ~FDescribePropertyFormsTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribePropertyFormsResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribePropertyFormsTask, ESPMode::ThreadSafe> FDescribePropertyFormsTaskPtr;
}