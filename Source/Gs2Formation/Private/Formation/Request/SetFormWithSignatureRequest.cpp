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

#include "Formation/Request/SetFormWithSignatureRequest.h"

namespace Gs2::Formation::Request
{
    FSetFormWithSignatureRequest::FSetFormWithSignatureRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        MoldModelNameValue(TOptional<FString>()),
        IndexValue(TOptional<int32>()),
        SlotsValue(nullptr),
        KeyIdValue(TOptional<FString>())
    {
    }

    FSetFormWithSignatureRequest::FSetFormWithSignatureRequest(
        const FSetFormWithSignatureRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        MoldModelNameValue(From.MoldModelNameValue),
        IndexValue(From.IndexValue),
        SlotsValue(From.SlotsValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FSetFormWithSignatureRequest> FSetFormWithSignatureRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormWithSignatureRequest> FSetFormWithSignatureRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormWithSignatureRequest> FSetFormWithSignatureRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormWithSignatureRequest> FSetFormWithSignatureRequest::WithMoldModelName(
        const TOptional<FString> MoldModelName
    )
    {
        this->MoldModelNameValue = MoldModelName;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormWithSignatureRequest> FSetFormWithSignatureRequest::WithIndex(
        const TOptional<int32> Index
    )
    {
        this->IndexValue = Index;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormWithSignatureRequest> FSetFormWithSignatureRequest::WithSlots(
        const TSharedPtr<TArray<TSharedPtr<Model::FSlotWithSignature>>> Slots
    )
    {
        this->SlotsValue = Slots;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormWithSignatureRequest> FSetFormWithSignatureRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormWithSignatureRequest> FSetFormWithSignatureRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSetFormWithSignatureRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSetFormWithSignatureRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSetFormWithSignatureRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FSetFormWithSignatureRequest::GetMoldModelName() const
    {
        return MoldModelNameValue;
    }

    TOptional<int32> FSetFormWithSignatureRequest::GetIndex() const
    {
        return IndexValue;
    }

    FString FSetFormWithSignatureRequest::GetIndexString() const
    {
        if (!IndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IndexValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FSlotWithSignature>>> FSetFormWithSignatureRequest::GetSlots() const
    {
        if (!SlotsValue.IsValid())
        {
            return nullptr;
        }
        return SlotsValue;
    }

    TOptional<FString> FSetFormWithSignatureRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TOptional<FString> FSetFormWithSignatureRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSetFormWithSignatureRequest> FSetFormWithSignatureRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetFormWithSignatureRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMoldModelName(Data->HasField(ANSI_TO_TCHAR("moldModelName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("moldModelName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithIndex(Data->HasField(ANSI_TO_TCHAR("index")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("index"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithSlots(Data->HasField(ANSI_TO_TCHAR("slots")) ? [Data]() -> TSharedPtr<TArray<Model::FSlotWithSignaturePtr>>
              {
                  auto v = MakeShared<TArray<Model::FSlotWithSignaturePtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("slots")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("slots")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("slots")))
                      {
                          v->Add(Model::FSlotWithSignature::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FSlotWithSignaturePtr>>())
            ->WithKeyId(Data->HasField(ANSI_TO_TCHAR("keyId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("keyId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSetFormWithSignatureRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (MoldModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("moldModelName", MoldModelNameValue.GetValue());
        }
        if (IndexValue.IsSet())
        {
            JsonRootObject->SetNumberField("index", IndexValue.GetValue());
        }
        if (SlotsValue != nullptr && SlotsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SlotsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("slots", v);
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}