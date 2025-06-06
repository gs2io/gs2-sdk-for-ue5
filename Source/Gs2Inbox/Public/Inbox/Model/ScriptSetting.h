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
#include "Core/Gs2Object.h"

namespace Gs2::Inbox::Model
{
    class GS2INBOX_API FScriptSetting final : public FGs2Object, public TSharedFromThis<FScriptSetting>
    {
        TOptional<FString> TriggerScriptIdValue;
        TOptional<FString> DoneTriggerTargetTypeValue;
        TOptional<FString> DoneTriggerScriptIdValue;
        TOptional<FString> DoneTriggerQueueNamespaceIdValue;

    public:
        FScriptSetting();
        FScriptSetting(
            const FScriptSetting& From
        );
        virtual ~FScriptSetting() override = default;

        TSharedPtr<FScriptSetting> WithTriggerScriptId(const TOptional<FString> TriggerScriptId);
        TSharedPtr<FScriptSetting> WithDoneTriggerTargetType(const TOptional<FString> DoneTriggerTargetType);
        TSharedPtr<FScriptSetting> WithDoneTriggerScriptId(const TOptional<FString> DoneTriggerScriptId);
        TSharedPtr<FScriptSetting> WithDoneTriggerQueueNamespaceId(const TOptional<FString> DoneTriggerQueueNamespaceId);

        TOptional<FString> GetTriggerScriptId() const;
        TOptional<FString> GetDoneTriggerTargetType() const;
        TOptional<FString> GetDoneTriggerScriptId() const;
        TOptional<FString> GetDoneTriggerQueueNamespaceId() const;


        static TSharedPtr<FScriptSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FScriptSetting, ESPMode::ThreadSafe> FScriptSettingPtr;
}