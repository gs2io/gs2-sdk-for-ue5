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

namespace Gs2::Realtime::Model
{
    class GS2REALTIME_API FParticipantSetting final : public FGs2Object, public TSharedFromThis<FParticipantSetting>
    {
        TOptional<FString> UserIdValue;
        TOptional<FString> ScriptIdValue;

    public:
        FParticipantSetting();
        FParticipantSetting(
            const FParticipantSetting& From
        );
        virtual ~FParticipantSetting() override = default;

        TSharedPtr<FParticipantSetting> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FParticipantSetting> WithScriptId(const TOptional<FString> ScriptId);

        TOptional<FString> GetUserId() const;
        TOptional<FString> GetScriptId() const;


        static TSharedPtr<FParticipantSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FParticipantSetting, ESPMode::ThreadSafe> FParticipantSettingPtr;
}