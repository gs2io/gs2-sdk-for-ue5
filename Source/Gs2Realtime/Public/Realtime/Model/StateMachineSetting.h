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
    class GS2REALTIME_API FStateMachineSetting final : public FGs2Object, public TSharedFromThis<FStateMachineSetting>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<int64> VersionValue;

    public:
        FStateMachineSetting();
        FStateMachineSetting(
            const FStateMachineSetting& From
        );
        virtual ~FStateMachineSetting() override = default;

        TSharedPtr<FStateMachineSetting> WithNamespaceId(const TOptional<FString> NamespaceId);
        TSharedPtr<FStateMachineSetting> WithVersion(const TOptional<int64> Version);

        TOptional<FString> GetNamespaceId() const;
        TOptional<int64> GetVersion() const;
        FString GetVersionString() const;


        static TSharedPtr<FStateMachineSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStateMachineSetting, ESPMode::ThreadSafe> FStateMachineSettingPtr;
}