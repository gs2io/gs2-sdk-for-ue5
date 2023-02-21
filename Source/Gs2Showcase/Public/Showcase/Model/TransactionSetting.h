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

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FTransactionSetting final : public TSharedFromThis<FTransactionSetting>
    {
        TOptional<bool> EnableAutoRunValue;
        TOptional<FString> DistributorNamespaceIdValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> QueueNamespaceIdValue;

    public:
        FTransactionSetting();
        FTransactionSetting(
            const FTransactionSetting& From
        );
        ~FTransactionSetting() = default;

        TSharedPtr<FTransactionSetting> WithEnableAutoRun(const TOptional<bool> EnableAutoRun);
        TSharedPtr<FTransactionSetting> WithDistributorNamespaceId(const TOptional<FString> DistributorNamespaceId);
        TSharedPtr<FTransactionSetting> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FTransactionSetting> WithQueueNamespaceId(const TOptional<FString> QueueNamespaceId);

        TOptional<bool> GetEnableAutoRun() const;
        FString GetEnableAutoRunString() const;
        TOptional<FString> GetDistributorNamespaceId() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetQueueNamespaceId() const;


        static TSharedPtr<FTransactionSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTransactionSetting, ESPMode::ThreadSafe> FTransactionSettingPtr;
}