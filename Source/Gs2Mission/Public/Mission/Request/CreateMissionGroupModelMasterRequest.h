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

namespace Gs2::Mission::Request
{
    class FCreateMissionGroupModelMasterRequest;

    class GS2MISSION_API FCreateMissionGroupModelMasterRequest final : public TSharedFromThis<FCreateMissionGroupModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;
        TOptional<FString> CompleteNotificationNamespaceIdValue;
        
    public:
        
        FCreateMissionGroupModelMasterRequest();
        FCreateMissionGroupModelMasterRequest(
            const FCreateMissionGroupModelMasterRequest& From
        );
        ~FCreateMissionGroupModelMasterRequest() = default;

        TSharedPtr<FCreateMissionGroupModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateMissionGroupModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateMissionGroupModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateMissionGroupModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateMissionGroupModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateMissionGroupModelMasterRequest> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FCreateMissionGroupModelMasterRequest> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FCreateMissionGroupModelMasterRequest> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FCreateMissionGroupModelMasterRequest> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FCreateMissionGroupModelMasterRequest> WithCompleteNotificationNamespaceId(const TOptional<FString> CompleteNotificationNamespaceId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetResetType() const;
        TOptional<int32> GetResetDayOfMonth() const;
        FString GetResetDayOfMonthString() const;
        TOptional<FString> GetResetDayOfWeek() const;
        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;
        TOptional<FString> GetCompleteNotificationNamespaceId() const;

        static TSharedPtr<FCreateMissionGroupModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateMissionGroupModelMasterRequest, ESPMode::ThreadSafe> FCreateMissionGroupModelMasterRequestPtr;
}