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

#include "Dictionary/Request/VerifyEntryCountRequest.h"

namespace Gs2::Dictionary::Request
{
    FVerifyEntryCountRequest::FVerifyEntryCountRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        EntryModelNamesValue(nullptr),
        VerifyTypeValue(TOptional<FString>()),
        CountValue(TOptional<int32>())
    {
    }

    FVerifyEntryCountRequest::FVerifyEntryCountRequest(
        const FVerifyEntryCountRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        EntryModelNamesValue(From.EntryModelNamesValue),
        VerifyTypeValue(From.VerifyTypeValue),
        CountValue(From.CountValue)
    {
    }

    TSharedPtr<FVerifyEntryCountRequest> FVerifyEntryCountRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyEntryCountRequest> FVerifyEntryCountRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyEntryCountRequest> FVerifyEntryCountRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyEntryCountRequest> FVerifyEntryCountRequest::WithEntryModelNames(
        const TSharedPtr<TArray<FString>> EntryModelNames
    )
    {
        this->EntryModelNamesValue = EntryModelNames;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyEntryCountRequest> FVerifyEntryCountRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyEntryCountRequest> FVerifyEntryCountRequest::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyEntryCountRequest> FVerifyEntryCountRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyEntryCountRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyEntryCountRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyEntryCountRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TSharedPtr<TArray<FString>> FVerifyEntryCountRequest::GetEntryModelNames() const
    {
        if (!EntryModelNamesValue.IsValid())
        {
            return nullptr;
        }
        return EntryModelNamesValue;
    }

    TOptional<FString> FVerifyEntryCountRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<int32> FVerifyEntryCountRequest::GetCount() const
    {
        return CountValue;
    }

    FString FVerifyEntryCountRequest::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    TOptional<FString> FVerifyEntryCountRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyEntryCountRequest> FVerifyEntryCountRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyEntryCountRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithEntryModelNames(Data->HasField(ANSI_TO_TCHAR("entryModelNames")) ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("entryModelNames")))
                  {
                      return nullptr;
                  }
                  auto v = MakeShared<TArray<FString>>();
                  for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("entryModelNames")))
                      {
                      v->Add(JsonObjectValue->AsString());
                      }
                  return v;
              }() : nullptr)
            ->WithVerifyType(Data->HasField(ANSI_TO_TCHAR("verifyType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyType"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCount(Data->HasField(ANSI_TO_TCHAR("count")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("count"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyEntryCountRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("contextStack"), ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("namespaceName"), NamespaceNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("xGs2AccessToken"), AccessTokenValue.GetValue());
        }
        if (EntryModelNamesValue != nullptr && EntryModelNamesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *EntryModelNamesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField(TEXT("entryModelNames"), v);
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("verifyType"), VerifyTypeValue.GetValue());
        }
        if (CountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("count"), CountValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("duplicationAvoider"), DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}