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
#include "Dom/JsonObject.h"

namespace Gs2::Lottery::Request
{
    class FDeleteLotteryModelMasterRequest;

    class GS2LOTTERY_API FDeleteLotteryModelMasterRequest final : public TSharedFromThis<FDeleteLotteryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LotteryNameValue;
        
    public:
        
        FDeleteLotteryModelMasterRequest();
        FDeleteLotteryModelMasterRequest(
            const FDeleteLotteryModelMasterRequest& From
        );
        ~FDeleteLotteryModelMasterRequest() = default;

        TSharedPtr<FDeleteLotteryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteLotteryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteLotteryModelMasterRequest> WithLotteryName(const TOptional<FString> LotteryName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLotteryName() const;

        static TSharedPtr<FDeleteLotteryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteLotteryModelMasterRequest> FDeleteLotteryModelMasterRequestPtr;
}