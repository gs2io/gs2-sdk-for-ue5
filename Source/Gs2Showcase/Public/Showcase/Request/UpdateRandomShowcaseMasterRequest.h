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
#include "../Model/RandomDisplayItemModel.h"

namespace Gs2::Showcase::Request
{
    class FUpdateRandomShowcaseMasterRequest;

    class GS2SHOWCASE_API FUpdateRandomShowcaseMasterRequest final : public TSharedFromThis<FUpdateRandomShowcaseMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> MaximumNumberOfChoiceValue;
        TSharedPtr<TArray<TSharedPtr<Model::FRandomDisplayItemModel>>> DisplayItemsValue;
        TOptional<int64> BaseTimestampValue;
        TOptional<int32> ResetIntervalHoursValue;
        TOptional<FString> SalesPeriodEventIdValue;
        
    public:
        
        FUpdateRandomShowcaseMasterRequest();
        FUpdateRandomShowcaseMasterRequest(
            const FUpdateRandomShowcaseMasterRequest& From
        );
        ~FUpdateRandomShowcaseMasterRequest() = default;

        TSharedPtr<FUpdateRandomShowcaseMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateRandomShowcaseMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateRandomShowcaseMasterRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FUpdateRandomShowcaseMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateRandomShowcaseMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateRandomShowcaseMasterRequest> WithMaximumNumberOfChoice(const TOptional<int32> MaximumNumberOfChoice);
        TSharedPtr<FUpdateRandomShowcaseMasterRequest> WithDisplayItems(const TSharedPtr<TArray<TSharedPtr<Model::FRandomDisplayItemModel>>> DisplayItems);
        TSharedPtr<FUpdateRandomShowcaseMasterRequest> WithBaseTimestamp(const TOptional<int64> BaseTimestamp);
        TSharedPtr<FUpdateRandomShowcaseMasterRequest> WithResetIntervalHours(const TOptional<int32> ResetIntervalHours);
        TSharedPtr<FUpdateRandomShowcaseMasterRequest> WithSalesPeriodEventId(const TOptional<FString> SalesPeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetMaximumNumberOfChoice() const;
        FString GetMaximumNumberOfChoiceString() const;TSharedPtr<TArray<TSharedPtr<Model::FRandomDisplayItemModel>>> GetDisplayItems() const;
        TOptional<int64> GetBaseTimestamp() const;
        FString GetBaseTimestampString() const;
        TOptional<int32> GetResetIntervalHours() const;
        FString GetResetIntervalHoursString() const;
        TOptional<FString> GetSalesPeriodEventId() const;

        static TSharedPtr<FUpdateRandomShowcaseMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateRandomShowcaseMasterRequest> FUpdateRandomShowcaseMasterRequestPtr;
}