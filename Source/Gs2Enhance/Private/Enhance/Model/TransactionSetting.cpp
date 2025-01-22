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

#include "Enhance/Model/TransactionSetting.h"

namespace Gs2::Enhance::Model
{
    FTransactionSetting::FTransactionSetting():
        EnableAutoRunValue(TOptional<bool>()),
        EnableAtomicCommitValue(TOptional<bool>()),
        TransactionUseDistributorValue(TOptional<bool>()),
        AcquireActionUseJobQueueValue(TOptional<bool>()),
        DistributorNamespaceIdValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>()),
        QueueNamespaceIdValue(TOptional<FString>())
    {
    }

    FTransactionSetting::FTransactionSetting(
        const FTransactionSetting& From
    ):
        EnableAutoRunValue(From.EnableAutoRunValue),
        EnableAtomicCommitValue(From.EnableAtomicCommitValue),
        TransactionUseDistributorValue(From.TransactionUseDistributorValue),
        AcquireActionUseJobQueueValue(From.AcquireActionUseJobQueueValue),
        DistributorNamespaceIdValue(From.DistributorNamespaceIdValue),
        KeyIdValue(From.KeyIdValue),
        QueueNamespaceIdValue(From.QueueNamespaceIdValue)
    {
    }

    TSharedPtr<FTransactionSetting> FTransactionSetting::WithEnableAutoRun(
        const TOptional<bool> EnableAutoRun
    )
    {
        this->EnableAutoRunValue = EnableAutoRun;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionSetting> FTransactionSetting::WithEnableAtomicCommit(
        const TOptional<bool> EnableAtomicCommit
    )
    {
        this->EnableAtomicCommitValue = EnableAtomicCommit;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionSetting> FTransactionSetting::WithTransactionUseDistributor(
        const TOptional<bool> TransactionUseDistributor
    )
    {
        this->TransactionUseDistributorValue = TransactionUseDistributor;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionSetting> FTransactionSetting::WithAcquireActionUseJobQueue(
        const TOptional<bool> AcquireActionUseJobQueue
    )
    {
        this->AcquireActionUseJobQueueValue = AcquireActionUseJobQueue;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionSetting> FTransactionSetting::WithDistributorNamespaceId(
        const TOptional<FString> DistributorNamespaceId
    )
    {
        this->DistributorNamespaceIdValue = DistributorNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionSetting> FTransactionSetting::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionSetting> FTransactionSetting::WithQueueNamespaceId(
        const TOptional<FString> QueueNamespaceId
    )
    {
        this->QueueNamespaceIdValue = QueueNamespaceId;
        return SharedThis(this);
    }
    TOptional<bool> FTransactionSetting::GetEnableAutoRun() const
    {
        return EnableAutoRunValue;
    }

    FString FTransactionSetting::GetEnableAutoRunString() const
    {
        if (!EnableAutoRunValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableAutoRunValue.GetValue() ? "true" : "false");
    }
    TOptional<bool> FTransactionSetting::GetEnableAtomicCommit() const
    {
        return EnableAtomicCommitValue;
    }

    FString FTransactionSetting::GetEnableAtomicCommitString() const
    {
        if (!EnableAtomicCommitValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableAtomicCommitValue.GetValue() ? "true" : "false");
    }
    TOptional<bool> FTransactionSetting::GetTransactionUseDistributor() const
    {
        return TransactionUseDistributorValue;
    }

    FString FTransactionSetting::GetTransactionUseDistributorString() const
    {
        if (!TransactionUseDistributorValue.IsSet())
        {
            return FString("null");
        }
        return FString(TransactionUseDistributorValue.GetValue() ? "true" : "false");
    }
    TOptional<bool> FTransactionSetting::GetAcquireActionUseJobQueue() const
    {
        return AcquireActionUseJobQueueValue;
    }

    FString FTransactionSetting::GetAcquireActionUseJobQueueString() const
    {
        if (!AcquireActionUseJobQueueValue.IsSet())
        {
            return FString("null");
        }
        return FString(AcquireActionUseJobQueueValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FTransactionSetting::GetDistributorNamespaceId() const
    {
        return DistributorNamespaceIdValue;
    }
    TOptional<FString> FTransactionSetting::GetKeyId() const
    {
        return KeyIdValue;
    }
    TOptional<FString> FTransactionSetting::GetQueueNamespaceId() const
    {
        return QueueNamespaceIdValue;
    }

    TSharedPtr<FTransactionSetting> FTransactionSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTransactionSetting>()
            ->WithEnableAutoRun(Data->HasField(ANSI_TO_TCHAR("enableAutoRun")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("enableAutoRun"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithEnableAtomicCommit(Data->HasField(ANSI_TO_TCHAR("enableAtomicCommit")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("enableAtomicCommit"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithTransactionUseDistributor(Data->HasField(ANSI_TO_TCHAR("transactionUseDistributor")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("transactionUseDistributor"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithAcquireActionUseJobQueue(Data->HasField(ANSI_TO_TCHAR("acquireActionUseJobQueue")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("acquireActionUseJobQueue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithDistributorNamespaceId(Data->HasField(ANSI_TO_TCHAR("distributorNamespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("distributorNamespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithKeyId(Data->HasField(ANSI_TO_TCHAR("keyId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("keyId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithQueueNamespaceId(Data->HasField(ANSI_TO_TCHAR("queueNamespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("queueNamespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FTransactionSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (EnableAutoRunValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableAutoRun", EnableAutoRunValue.GetValue());
        }
        if (EnableAtomicCommitValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableAtomicCommit", EnableAtomicCommitValue.GetValue());
        }
        if (TransactionUseDistributorValue.IsSet())
        {
            JsonRootObject->SetBoolField("transactionUseDistributor", TransactionUseDistributorValue.GetValue());
        }
        if (AcquireActionUseJobQueueValue.IsSet())
        {
            JsonRootObject->SetBoolField("acquireActionUseJobQueue", AcquireActionUseJobQueueValue.GetValue());
        }
        if (DistributorNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("distributorNamespaceId", DistributorNamespaceIdValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        if (QueueNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("queueNamespaceId", QueueNamespaceIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FTransactionSetting::TypeName = "TransactionSetting";
}