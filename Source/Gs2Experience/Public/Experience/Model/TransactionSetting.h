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

namespace Gs2::Experience::Model
{
    class GS2EXPERIENCE_API FTransactionSetting final : public FGs2Object, public TSharedFromThis<FTransactionSetting>
    {
        TOptional<bool> EnableAutoRunValue;
        TOptional<bool> EnableAtomicCommitValue;
        TOptional<bool> TransactionUseDistributorValue;
        TOptional<bool> AcquireActionUseJobQueueValue;
        TOptional<FString> DistributorNamespaceIdValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> QueueNamespaceIdValue;

    public:
        FTransactionSetting();
        FTransactionSetting(
            const FTransactionSetting& From
        );
        virtual ~FTransactionSetting() override = default;

        TSharedPtr<FTransactionSetting> WithEnableAutoRun(const TOptional<bool> EnableAutoRun);
        TSharedPtr<FTransactionSetting> WithEnableAtomicCommit(const TOptional<bool> EnableAtomicCommit);
        TSharedPtr<FTransactionSetting> WithTransactionUseDistributor(const TOptional<bool> TransactionUseDistributor);
        TSharedPtr<FTransactionSetting> WithAcquireActionUseJobQueue(const TOptional<bool> AcquireActionUseJobQueue);
        TSharedPtr<FTransactionSetting> WithDistributorNamespaceId(const TOptional<FString> DistributorNamespaceId);
        TSharedPtr<FTransactionSetting> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FTransactionSetting> WithQueueNamespaceId(const TOptional<FString> QueueNamespaceId);

        TOptional<bool> GetEnableAutoRun() const;
        FString GetEnableAutoRunString() const;
        TOptional<bool> GetEnableAtomicCommit() const;
        FString GetEnableAtomicCommitString() const;
        TOptional<bool> GetTransactionUseDistributor() const;
        FString GetTransactionUseDistributorString() const;
        TOptional<bool> GetAcquireActionUseJobQueue() const;
        FString GetAcquireActionUseJobQueueString() const;
        TOptional<FString> GetDistributorNamespaceId() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetQueueNamespaceId() const;


        static TSharedPtr<FTransactionSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTransactionSetting, ESPMode::ThreadSafe> FTransactionSettingPtr;
}