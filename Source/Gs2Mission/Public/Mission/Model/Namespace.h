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
#include "TransactionSetting.h"
#include "ScriptSetting.h"
#include "NotificationSetting.h"
#include "LogSetting.h"

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FNamespace final : public TSharedFromThis<FNamespace>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<FTransactionSetting> TransactionSettingValue;
        TSharedPtr<FScriptSetting> MissionCompleteScriptValue;
        TSharedPtr<FScriptSetting> CounterIncrementScriptValue;
        TSharedPtr<FScriptSetting> ReceiveRewardsScriptValue;
        TSharedPtr<FNotificationSetting> CompleteNotificationValue;
        TSharedPtr<FLogSetting> LogSettingValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<FString> QueueNamespaceIdValue;
        TOptional<FString> KeyIdValue;

    public:
        FNamespace();
        FNamespace(
            const FNamespace& From
        );
        ~FNamespace() = default;

        TSharedPtr<FNamespace> WithNamespaceId(const TOptional<FString> NamespaceId);
        TSharedPtr<FNamespace> WithName(const TOptional<FString> Name);
        TSharedPtr<FNamespace> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FNamespace> WithTransactionSetting(const TSharedPtr<FTransactionSetting> TransactionSetting);
        TSharedPtr<FNamespace> WithMissionCompleteScript(const TSharedPtr<FScriptSetting> MissionCompleteScript);
        TSharedPtr<FNamespace> WithCounterIncrementScript(const TSharedPtr<FScriptSetting> CounterIncrementScript);
        TSharedPtr<FNamespace> WithReceiveRewardsScript(const TSharedPtr<FScriptSetting> ReceiveRewardsScript);
        TSharedPtr<FNamespace> WithCompleteNotification(const TSharedPtr<FNotificationSetting> CompleteNotification);
        TSharedPtr<FNamespace> WithLogSetting(const TSharedPtr<FLogSetting> LogSetting);
        TSharedPtr<FNamespace> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FNamespace> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FNamespace> WithQueueNamespaceId(const TOptional<FString> QueueNamespaceId);
        TSharedPtr<FNamespace> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<FTransactionSetting> GetTransactionSetting() const;
        TSharedPtr<FScriptSetting> GetMissionCompleteScript() const;
        TSharedPtr<FScriptSetting> GetCounterIncrementScript() const;
        TSharedPtr<FScriptSetting> GetReceiveRewardsScript() const;
        TSharedPtr<FNotificationSetting> GetCompleteNotification() const;
        TSharedPtr<FLogSetting> GetLogSetting() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<FString> GetQueueNamespaceId() const;
        TOptional<FString> GetKeyId() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);

        static TSharedPtr<FNamespace> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FNamespace, ESPMode::ThreadSafe> FNamespacePtr;
}