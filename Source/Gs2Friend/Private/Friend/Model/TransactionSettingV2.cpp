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

#include "Friend/Model/TransactionSettingV2.h"

namespace Gs2::Friend::Model
{
    FTransactionSettingV2::FTransactionSettingV2():
        DistributorNamespaceIdValue(TOptional<FString>()),
        EnableParallelExecutionValue(TOptional<bool>())
    {
    }

    FTransactionSettingV2::FTransactionSettingV2(
        const FTransactionSettingV2& From
    ):
        DistributorNamespaceIdValue(From.DistributorNamespaceIdValue),
        EnableParallelExecutionValue(From.EnableParallelExecutionValue)
    {
    }

    TSharedPtr<FTransactionSettingV2> FTransactionSettingV2::WithDistributorNamespaceId(
        const TOptional<FString> DistributorNamespaceId
    )
    {
        this->DistributorNamespaceIdValue = DistributorNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionSettingV2> FTransactionSettingV2::WithEnableParallelExecution(
        const TOptional<bool> EnableParallelExecution
    )
    {
        this->EnableParallelExecutionValue = EnableParallelExecution;
        return SharedThis(this);
    }
    TOptional<FString> FTransactionSettingV2::GetDistributorNamespaceId() const
    {
        return DistributorNamespaceIdValue;
    }
    TOptional<bool> FTransactionSettingV2::GetEnableParallelExecution() const
    {
        return EnableParallelExecutionValue;
    }

    FString FTransactionSettingV2::GetEnableParallelExecutionString() const
    {
        if (!EnableParallelExecutionValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableParallelExecutionValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FTransactionSettingV2> FTransactionSettingV2::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTransactionSettingV2>()
            ->WithDistributorNamespaceId(Data->HasField(ANSI_TO_TCHAR("distributorNamespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("distributorNamespaceId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithEnableParallelExecution(Data->HasField(ANSI_TO_TCHAR("enableParallelExecution")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("enableParallelExecution"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FTransactionSettingV2::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DistributorNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("distributorNamespaceId"), DistributorNamespaceIdValue.GetValue());
        }
        if (EnableParallelExecutionValue.IsSet())
        {
            JsonRootObject->SetBoolField(TEXT("enableParallelExecution"), EnableParallelExecutionValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FTransactionSettingV2::TypeName = "TransactionSettingV2";
}