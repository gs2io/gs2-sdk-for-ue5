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
#include "Chat/Request/DescribeCategoryModelMastersRequest.h"
#include "Chat/Result/DescribeCategoryModelMastersResult.h"

namespace Gs2::Chat::Task::WebSocket
{
    class GS2CHAT_API FDescribeCategoryModelMastersTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeCategoryModelMastersResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FDescribeCategoryModelMastersRequestPtr Request;
    public:
        explicit FDescribeCategoryModelMastersTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FDescribeCategoryModelMastersRequestPtr Request
        );
        FDescribeCategoryModelMastersTask(
            const FDescribeCategoryModelMastersTask& From
        );
        virtual ~FDescribeCategoryModelMastersTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeCategoryModelMastersResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeCategoryModelMastersTask, ESPMode::ThreadSafe> FDescribeCategoryModelMastersTaskPtr;
}