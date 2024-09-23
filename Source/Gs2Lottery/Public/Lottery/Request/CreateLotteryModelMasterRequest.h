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
    class FCreateLotteryModelMasterRequest;

    class GS2LOTTERY_API FCreateLotteryModelMasterRequest final : public TSharedFromThis<FCreateLotteryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ModeValue;
        TOptional<FString> MethodValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<FString> ChoicePrizeTableScriptIdValue;
        
    public:
        
        FCreateLotteryModelMasterRequest();
        FCreateLotteryModelMasterRequest(
            const FCreateLotteryModelMasterRequest& From
        );
        ~FCreateLotteryModelMasterRequest() = default;

        TSharedPtr<FCreateLotteryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateLotteryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateLotteryModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateLotteryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateLotteryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateLotteryModelMasterRequest> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FCreateLotteryModelMasterRequest> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FCreateLotteryModelMasterRequest> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FCreateLotteryModelMasterRequest> WithChoicePrizeTableScriptId(const TOptional<FString> ChoicePrizeTableScriptId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetMethod() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<FString> GetChoicePrizeTableScriptId() const;

        static TSharedPtr<FCreateLotteryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateLotteryModelMasterRequest, ESPMode::ThreadSafe> FCreateLotteryModelMasterRequestPtr;
}