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
#include "../Model/TransactionSetting.h"
#include "../Model/TransactionSettingV2.h"
#include "../Model/SyncSetting.h"
#include "../Model/StateMachineSetting.h"
#include "../Model/ParticipantSetting.h"
#include "../Model/NotificationSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Realtime::Request
{
    class FUpdateNamespaceRequest;

    class GS2REALTIME_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FTransactionSetting> TransactionSettingValue;
        TSharedPtr<Model::FTransactionSettingV2> TransactionSettingV2Value;
        TOptional<FString> ServerTypeValue;
        TOptional<FString> ServerSpecValue;
        TSharedPtr<Model::FSyncSetting> SyncSettingValue;
        TSharedPtr<Model::FStateMachineSetting> StateMachineSettingValue;
        TSharedPtr<Model::FParticipantSetting> ParticipantSettingValue;
        TSharedPtr<Model::FNotificationSetting> CreateNotificationValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        
    public:
        
        FUpdateNamespaceRequest();
        FUpdateNamespaceRequest(
            const FUpdateNamespaceRequest& From
        );
        ~FUpdateNamespaceRequest() = default;

        TSharedPtr<FUpdateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateNamespaceRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateNamespaceRequest> WithTransactionSetting(const TSharedPtr<Model::FTransactionSetting> TransactionSetting);
        TSharedPtr<FUpdateNamespaceRequest> WithTransactionSettingV2(const TSharedPtr<Model::FTransactionSettingV2> TransactionSettingV2);
        TSharedPtr<FUpdateNamespaceRequest> WithServerType(const TOptional<FString> ServerType);
        TSharedPtr<FUpdateNamespaceRequest> WithServerSpec(const TOptional<FString> ServerSpec);
        TSharedPtr<FUpdateNamespaceRequest> WithSyncSetting(const TSharedPtr<Model::FSyncSetting> SyncSetting);
        TSharedPtr<FUpdateNamespaceRequest> WithStateMachineSetting(const TSharedPtr<Model::FStateMachineSetting> StateMachineSetting);
        TSharedPtr<FUpdateNamespaceRequest> WithParticipantSetting(const TSharedPtr<Model::FParticipantSetting> ParticipantSetting);
        TSharedPtr<FUpdateNamespaceRequest> WithCreateNotification(const TSharedPtr<Model::FNotificationSetting> CreateNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FTransactionSetting> GetTransactionSetting() const;
        TSharedPtr<Model::FTransactionSettingV2> GetTransactionSettingV2() const;
        TOptional<FString> GetServerType() const;
        TOptional<FString> GetServerSpec() const;
        TSharedPtr<Model::FSyncSetting> GetSyncSetting() const;
        TSharedPtr<Model::FStateMachineSetting> GetStateMachineSetting() const;
        TSharedPtr<Model::FParticipantSetting> GetParticipantSetting() const;
        TSharedPtr<Model::FNotificationSetting> GetCreateNotification() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequestPtr;
}