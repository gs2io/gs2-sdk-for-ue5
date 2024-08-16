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
#include "../Model/Prize.h"

namespace Gs2::Lottery::Request
{
    class FUpdatePrizeTableMasterRequest;

    class GS2LOTTERY_API FUpdatePrizeTableMasterRequest final : public TSharedFromThis<FUpdatePrizeTableMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FPrize>>> PrizesValue;
        
    public:
        
        FUpdatePrizeTableMasterRequest();
        FUpdatePrizeTableMasterRequest(
            const FUpdatePrizeTableMasterRequest& From
        );
        ~FUpdatePrizeTableMasterRequest() = default;

        TSharedPtr<FUpdatePrizeTableMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdatePrizeTableMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdatePrizeTableMasterRequest> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FUpdatePrizeTableMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdatePrizeTableMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdatePrizeTableMasterRequest> WithPrizes(const TSharedPtr<TArray<TSharedPtr<Model::FPrize>>> Prizes);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FPrize>>> GetPrizes() const;

        static TSharedPtr<FUpdatePrizeTableMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdatePrizeTableMasterRequest> FUpdatePrizeTableMasterRequestPtr;
}