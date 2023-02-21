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

namespace Gs2::Lottery::Request
{
    class FUpdateLotteryModelMasterRequest;

    class GS2LOTTERY_API FUpdateLotteryModelMasterRequest final : public TSharedFromThis<FUpdateLotteryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LotteryNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ModeValue;
        TOptional<FString> MethodValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<FString> ChoicePrizeTableScriptIdValue;
        
    public:
        
        FUpdateLotteryModelMasterRequest();
        FUpdateLotteryModelMasterRequest(
            const FUpdateLotteryModelMasterRequest& From
        );
        ~FUpdateLotteryModelMasterRequest() = default;

        TSharedPtr<FUpdateLotteryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateLotteryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateLotteryModelMasterRequest> WithLotteryName(const TOptional<FString> LotteryName);
        TSharedPtr<FUpdateLotteryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateLotteryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateLotteryModelMasterRequest> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FUpdateLotteryModelMasterRequest> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FUpdateLotteryModelMasterRequest> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FUpdateLotteryModelMasterRequest> WithChoicePrizeTableScriptId(const TOptional<FString> ChoicePrizeTableScriptId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLotteryName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetMethod() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<FString> GetChoicePrizeTableScriptId() const;

        static TSharedPtr<FUpdateLotteryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateLotteryModelMasterRequest, ESPMode::ThreadSafe> FUpdateLotteryModelMasterRequestPtr;
}