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
#include "Money2/Request/TakeoverSubscriptionStatusRequest.h"
#include "Money2/Result/TakeoverSubscriptionStatusResult.h"

namespace Gs2::Money2::Task::Rest
{
    class GS2MONEY2_API FTakeoverSubscriptionStatusTask final : public Gs2::Core::Util::TGs2Future<Result::FTakeoverSubscriptionStatusResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FTakeoverSubscriptionStatusRequestPtr Request;
    public:
        explicit FTakeoverSubscriptionStatusTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FTakeoverSubscriptionStatusRequestPtr Request
        );
        FTakeoverSubscriptionStatusTask(
            const FTakeoverSubscriptionStatusTask& From
        );
        virtual ~FTakeoverSubscriptionStatusTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FTakeoverSubscriptionStatusResultPtr> Result) override;
    protected:
        virtual void OnError(Core::Model::FGs2ErrorPtr Error) override;
    };
    typedef TSharedPtr<FTakeoverSubscriptionStatusTask, ESPMode::ThreadSafe> FTakeoverSubscriptionStatusTaskPtr;
}