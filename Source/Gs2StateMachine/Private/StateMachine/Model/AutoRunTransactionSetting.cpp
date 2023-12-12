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

#include "StateMachine/Model/AutoRunTransactionSetting.h"

namespace Gs2::StateMachine::Model
{
    FAutoRunTransactionSetting::FAutoRunTransactionSetting():
        DistributorNamespaceIdValue(TOptional<FString>()),
        QueueNamespaceIdValue(TOptional<FString>())
    {
    }

    FAutoRunTransactionSetting::FAutoRunTransactionSetting(
        const FAutoRunTransactionSetting& From
    ):
        DistributorNamespaceIdValue(From.DistributorNamespaceIdValue),
        QueueNamespaceIdValue(From.QueueNamespaceIdValue)
    {
    }

    TSharedPtr<FAutoRunTransactionSetting> FAutoRunTransactionSetting::WithDistributorNamespaceId(
        const TOptional<FString> DistributorNamespaceId
    )
    {
        this->DistributorNamespaceIdValue = DistributorNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FAutoRunTransactionSetting> FAutoRunTransactionSetting::WithQueueNamespaceId(
        const TOptional<FString> QueueNamespaceId
    )
    {
        this->QueueNamespaceIdValue = QueueNamespaceId;
        return SharedThis(this);
    }
    TOptional<FString> FAutoRunTransactionSetting::GetDistributorNamespaceId() const
    {
        return DistributorNamespaceIdValue;
    }
    TOptional<FString> FAutoRunTransactionSetting::GetQueueNamespaceId() const
    {
        return QueueNamespaceIdValue;
    }

    TSharedPtr<FAutoRunTransactionSetting> FAutoRunTransactionSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAutoRunTransactionSetting>()
            ->WithDistributorNamespaceId(Data->HasField("distributorNamespaceId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("distributorNamespaceId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithQueueNamespaceId(Data->HasField("queueNamespaceId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("queueNamespaceId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAutoRunTransactionSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DistributorNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("distributorNamespaceId", DistributorNamespaceIdValue.GetValue());
        }
        if (QueueNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("queueNamespaceId", QueueNamespaceIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAutoRunTransactionSetting::TypeName = "AutoRunTransactionSetting";
}