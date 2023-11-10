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

#include "Stamina/Request/DeleteMaxStaminaTableMasterRequest.h"

namespace Gs2::Stamina::Request
{
    FDeleteMaxStaminaTableMasterRequest::FDeleteMaxStaminaTableMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        MaxStaminaTableNameValue(TOptional<FString>())
    {
    }

    FDeleteMaxStaminaTableMasterRequest::FDeleteMaxStaminaTableMasterRequest(
        const FDeleteMaxStaminaTableMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        MaxStaminaTableNameValue(From.MaxStaminaTableNameValue)
    {
    }

    TSharedPtr<FDeleteMaxStaminaTableMasterRequest> FDeleteMaxStaminaTableMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteMaxStaminaTableMasterRequest> FDeleteMaxStaminaTableMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteMaxStaminaTableMasterRequest> FDeleteMaxStaminaTableMasterRequest::WithMaxStaminaTableName(
        const TOptional<FString> MaxStaminaTableName
    )
    {
        this->MaxStaminaTableNameValue = MaxStaminaTableName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteMaxStaminaTableMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteMaxStaminaTableMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteMaxStaminaTableMasterRequest::GetMaxStaminaTableName() const
    {
        return MaxStaminaTableNameValue;
    }

    TSharedPtr<FDeleteMaxStaminaTableMasterRequest> FDeleteMaxStaminaTableMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteMaxStaminaTableMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMaxStaminaTableName(Data->HasField("maxStaminaTableName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("maxStaminaTableName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteMaxStaminaTableMasterRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (MaxStaminaTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("maxStaminaTableName", MaxStaminaTableNameValue.GetValue());
        }
        return JsonRootObject;
    }
}