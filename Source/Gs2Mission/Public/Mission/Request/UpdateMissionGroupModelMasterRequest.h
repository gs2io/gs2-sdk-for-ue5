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

namespace Gs2::Mission::Request
{
    class FUpdateMissionGroupModelMasterRequest;

    class GS2MISSION_API FUpdateMissionGroupModelMasterRequest final : public TSharedFromThis<FUpdateMissionGroupModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;
        TOptional<FString> CompleteNotificationNamespaceIdValue;
        
    public:
        
        FUpdateMissionGroupModelMasterRequest();
        FUpdateMissionGroupModelMasterRequest(
            const FUpdateMissionGroupModelMasterRequest& From
        );
        ~FUpdateMissionGroupModelMasterRequest() = default;

        TSharedPtr<FUpdateMissionGroupModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateMissionGroupModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateMissionGroupModelMasterRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FUpdateMissionGroupModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateMissionGroupModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateMissionGroupModelMasterRequest> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FUpdateMissionGroupModelMasterRequest> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FUpdateMissionGroupModelMasterRequest> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FUpdateMissionGroupModelMasterRequest> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FUpdateMissionGroupModelMasterRequest> WithCompleteNotificationNamespaceId(const TOptional<FString> CompleteNotificationNamespaceId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetResetType() const;
        TOptional<int32> GetResetDayOfMonth() const;
        FString GetResetDayOfMonthString() const;
        TOptional<FString> GetResetDayOfWeek() const;
        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;
        TOptional<FString> GetCompleteNotificationNamespaceId() const;

        static TSharedPtr<FUpdateMissionGroupModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequestPtr;
}