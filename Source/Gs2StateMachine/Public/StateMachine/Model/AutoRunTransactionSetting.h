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

namespace Gs2::StateMachine::Model
{
    class GS2STATEMACHINE_API FAutoRunTransactionSetting final : public FGs2Object, public TSharedFromThis<FAutoRunTransactionSetting>
    {
        TOptional<FString> DistributorNamespaceIdValue;
        TOptional<FString> QueueNamespaceIdValue;

    public:
        FAutoRunTransactionSetting();
        FAutoRunTransactionSetting(
            const FAutoRunTransactionSetting& From
        );
        virtual ~FAutoRunTransactionSetting() override = default;

        TSharedPtr<FAutoRunTransactionSetting> WithDistributorNamespaceId(const TOptional<FString> DistributorNamespaceId);
        TSharedPtr<FAutoRunTransactionSetting> WithQueueNamespaceId(const TOptional<FString> QueueNamespaceId);

        TOptional<FString> GetDistributorNamespaceId() const;
        TOptional<FString> GetQueueNamespaceId() const;


        static TSharedPtr<FAutoRunTransactionSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAutoRunTransactionSetting, ESPMode::ThreadSafe> FAutoRunTransactionSettingPtr;
}