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

#include "Formation/Request/SetFormByUserIdRequest.h"

namespace Gs2::Formation::Request
{
    FSetFormByUserIdRequest::FSetFormByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        MoldNameValue(TOptional<FString>()),
        IndexValue(TOptional<int32>()),
        SlotsValue(nullptr)
    {
    }

    FSetFormByUserIdRequest::FSetFormByUserIdRequest(
        const FSetFormByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        MoldNameValue(From.MoldNameValue),
        IndexValue(From.IndexValue),
        SlotsValue(From.SlotsValue)
    {
    }

    TSharedPtr<FSetFormByUserIdRequest> FSetFormByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormByUserIdRequest> FSetFormByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormByUserIdRequest> FSetFormByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormByUserIdRequest> FSetFormByUserIdRequest::WithMoldName(
        const TOptional<FString> MoldName
    )
    {
        this->MoldNameValue = MoldName;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormByUserIdRequest> FSetFormByUserIdRequest::WithIndex(
        const TOptional<int32> Index
    )
    {
        this->IndexValue = Index;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormByUserIdRequest> FSetFormByUserIdRequest::WithSlots(
        const TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> Slots
    )
    {
        this->SlotsValue = Slots;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormByUserIdRequest> FSetFormByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSetFormByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSetFormByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSetFormByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FSetFormByUserIdRequest::GetMoldName() const
    {
        return MoldNameValue;
    }

    TOptional<int32> FSetFormByUserIdRequest::GetIndex() const
    {
        return IndexValue;
    }

    FString FSetFormByUserIdRequest::GetIndexString() const
    {
        if (!IndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), IndexValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> FSetFormByUserIdRequest::GetSlots() const
    {
        if (!SlotsValue.IsValid())
        {
            return nullptr;
        }
        return SlotsValue;
    }

    TOptional<FString> FSetFormByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSetFormByUserIdRequest> FSetFormByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetFormByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMoldName(Data->HasField("moldName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("moldName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithIndex(Data->HasField("index") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("index", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithSlots(Data->HasField("slots") ? [Data]() -> TSharedPtr<TArray<Model::FSlotPtr>>
              {
                  auto v = MakeShared<TArray<Model::FSlotPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("slots") && Data->HasTypedField<EJson::Array>("slots"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("slots"))
                      {
                          v->Add(Model::FSlot::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSetFormByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (MoldNameValue.IsSet())
        {
            JsonRootObject->SetStringField("moldName", MoldNameValue.GetValue());
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
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}