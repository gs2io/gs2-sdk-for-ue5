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

#include "Stamina/Request/DeleteRecoverIntervalTableMasterRequest.h"

namespace Gs2::Stamina::Request
{
    FDeleteRecoverIntervalTableMasterRequest::FDeleteRecoverIntervalTableMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        RecoverIntervalTableNameValue(TOptional<FString>())
    {
    }

    FDeleteRecoverIntervalTableMasterRequest::FDeleteRecoverIntervalTableMasterRequest(
        const FDeleteRecoverIntervalTableMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RecoverIntervalTableNameValue(From.RecoverIntervalTableNameValue)
    {
    }

    TSharedPtr<FDeleteRecoverIntervalTableMasterRequest> FDeleteRecoverIntervalTableMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteRecoverIntervalTableMasterRequest> FDeleteRecoverIntervalTableMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteRecoverIntervalTableMasterRequest> FDeleteRecoverIntervalTableMasterRequest::WithRecoverIntervalTableName(
        const TOptional<FString> RecoverIntervalTableName
    )
    {
        this->RecoverIntervalTableNameValue = RecoverIntervalTableName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteRecoverIntervalTableMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteRecoverIntervalTableMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteRecoverIntervalTableMasterRequest::GetRecoverIntervalTableName() const
    {
        return RecoverIntervalTableNameValue;
    }

    TSharedPtr<FDeleteRecoverIntervalTableMasterRequest> FDeleteRecoverIntervalTableMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteRecoverIntervalTableMasterRequest>()
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
            ->WithRecoverIntervalTableName(Data->HasField("recoverIntervalTableName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("recoverIntervalTableName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteRecoverIntervalTableMasterRequest::ToJson() const
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
        if (RecoverIntervalTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("recoverIntervalTableName", RecoverIntervalTableNameValue.GetValue());
        }
        return JsonRootObject;
    }
}