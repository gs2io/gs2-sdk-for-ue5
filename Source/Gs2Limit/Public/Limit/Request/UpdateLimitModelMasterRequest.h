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

namespace Gs2::Limit::Request
{
    class FUpdateLimitModelMasterRequest;

    class GS2LIMIT_API FUpdateLimitModelMasterRequest final : public TSharedFromThis<FUpdateLimitModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LimitNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;
        
    public:
        
        FUpdateLimitModelMasterRequest();
        FUpdateLimitModelMasterRequest(
            const FUpdateLimitModelMasterRequest& From
        );
        ~FUpdateLimitModelMasterRequest() = default;

        TSharedPtr<FUpdateLimitModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateLimitModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateLimitModelMasterRequest> WithLimitName(const TOptional<FString> LimitName);
        TSharedPtr<FUpdateLimitModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateLimitModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateLimitModelMasterRequest> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FUpdateLimitModelMasterRequest> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FUpdateLimitModelMasterRequest> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FUpdateLimitModelMasterRequest> WithResetHour(const TOptional<int32> ResetHour);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLimitName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetResetType() const;
        TOptional<int32> GetResetDayOfMonth() const;
        FString GetResetDayOfMonthString() const;
        TOptional<FString> GetResetDayOfWeek() const;
        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;

        static TSharedPtr<FUpdateLimitModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateLimitModelMasterRequest> FUpdateLimitModelMasterRequestPtr;
}