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

#include "Stamina/Request/DeleteRecoverValueTableMasterRequest.h"

namespace Gs2::Stamina::Request
{
    FDeleteRecoverValueTableMasterRequest::FDeleteRecoverValueTableMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        RecoverValueTableNameValue(TOptional<FString>())
    {
    }

    FDeleteRecoverValueTableMasterRequest::FDeleteRecoverValueTableMasterRequest(
        const FDeleteRecoverValueTableMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RecoverValueTableNameValue(From.RecoverValueTableNameValue)
    {
    }

    TSharedPtr<FDeleteRecoverValueTableMasterRequest> FDeleteRecoverValueTableMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteRecoverValueTableMasterRequest> FDeleteRecoverValueTableMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteRecoverValueTableMasterRequest> FDeleteRecoverValueTableMasterRequest::WithRecoverValueTableName(
        const TOptional<FString> RecoverValueTableName
    )
    {
        this->RecoverValueTableNameValue = RecoverValueTableName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteRecoverValueTableMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteRecoverValueTableMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteRecoverValueTableMasterRequest::GetRecoverValueTableName() const
    {
        return RecoverValueTableNameValue;
    }

    TSharedPtr<FDeleteRecoverValueTableMasterRequest> FDeleteRecoverValueTableMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteRecoverValueTableMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRecoverValueTableName(Data->HasField("recoverValueTableName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("recoverValueTableName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteRecoverValueTableMasterRequest::ToJson() const
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
        if (RecoverValueTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("recoverValueTableName", RecoverValueTableNameValue.GetValue());
        }
        return JsonRootObject;
    }
}