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

namespace Gs2::Limit::Request
{
    class FCreateLimitModelMasterRequest;

    class GS2LIMIT_API FCreateLimitModelMasterRequest final : public TSharedFromThis<FCreateLimitModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;
        
    public:
        
        FCreateLimitModelMasterRequest();
        FCreateLimitModelMasterRequest(
            const FCreateLimitModelMasterRequest& From
        );
        ~FCreateLimitModelMasterRequest() = default;

        TSharedPtr<FCreateLimitModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateLimitModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateLimitModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateLimitModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateLimitModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateLimitModelMasterRequest> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FCreateLimitModelMasterRequest> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FCreateLimitModelMasterRequest> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FCreateLimitModelMasterRequest> WithResetHour(const TOptional<int32> ResetHour);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetResetType() const;
        TOptional<int32> GetResetDayOfMonth() const;
        FString GetResetDayOfMonthString() const;
        TOptional<FString> GetResetDayOfWeek() const;
        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;

        static TSharedPtr<FCreateLimitModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateLimitModelMasterRequest, ESPMode::ThreadSafe> FCreateLimitModelMasterRequestPtr;
}