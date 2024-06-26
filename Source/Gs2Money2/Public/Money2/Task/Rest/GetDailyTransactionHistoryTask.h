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
#include "Money2/Request/GetDailyTransactionHistoryRequest.h"
#include "Money2/Result/GetDailyTransactionHistoryResult.h"

namespace Gs2::Money2::Task::Rest
{
    class GS2MONEY2_API FGetDailyTransactionHistoryTask final : public Gs2::Core::Util::TGs2Future<Result::FGetDailyTransactionHistoryResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetDailyTransactionHistoryRequestPtr Request;
    public:
        explicit FGetDailyTransactionHistoryTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetDailyTransactionHistoryRequestPtr Request
        );
        FGetDailyTransactionHistoryTask(
            const FGetDailyTransactionHistoryTask& From
        );
        virtual ~FGetDailyTransactionHistoryTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetDailyTransactionHistoryResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetDailyTransactionHistoryTask, ESPMode::ThreadSafe> FGetDailyTransactionHistoryTaskPtr;
}