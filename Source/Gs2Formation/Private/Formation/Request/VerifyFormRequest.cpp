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

#include "Formation/Request/VerifyFormRequest.h"

namespace Gs2::Formation::Request
{
    FVerifyFormRequest::FVerifyFormRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        MoldModelNameValue(TOptional<FString>()),
        IndexValue(TOptional<int32>()),
        SlotNameValue(TOptional<FString>()),
        PropertyIdRegexValue(TOptional<FString>()),
        CountTypeValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        CountValue(TOptional<int32>())
    {
    }

    FVerifyFormRequest::FVerifyFormRequest(
        const FVerifyFormRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        MoldModelNameValue(From.MoldModelNameValue),
        IndexValue(From.IndexValue),
        SlotNameValue(From.SlotNameValue),
        PropertyIdRegexValue(From.PropertyIdRegexValue),
        CountTypeValue(From.CountTypeValue),
        VerifyTypeValue(From.VerifyTypeValue),
        CountValue(From.CountValue)
    {
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::WithMoldModelName(
        const TOptional<FString> MoldModelName
    )
    {
        this->MoldModelNameValue = MoldModelName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::WithIndex(
        const TOptional<int32> Index
    )
    {
        this->IndexValue = Index;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::WithSlotName(
        const TOptional<FString> SlotName
    )
    {
        this->SlotNameValue = SlotName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::WithPropertyIdRegex(
        const TOptional<FString> PropertyIdRegex
    )
    {
        this->PropertyIdRegexValue = PropertyIdRegex;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::WithCountType(
        const TOptional<FString> CountType
    )
    {
        this->CountTypeValue = CountType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyFormRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyFormRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyFormRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FVerifyFormRequest::GetMoldModelName() const
    {
        return MoldModelNameValue;
    }

    TOptional<int32> FVerifyFormRequest::GetIndex() const
    {
        return IndexValue;
    }

    FString FVerifyFormRequest::GetIndexString() const
    {
        if (!IndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IndexValue.GetValue());
    }

    TOptional<FString> FVerifyFormRequest::GetSlotName() const
    {
        return SlotNameValue;
    }

    TOptional<FString> FVerifyFormRequest::GetPropertyIdRegex() const
    {
        return PropertyIdRegexValue;
    }

    TOptional<FString> FVerifyFormRequest::GetCountType() const
    {
        return CountTypeValue;
    }

    TOptional<FString> FVerifyFormRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<int32> FVerifyFormRequest::GetCount() const
    {
        return CountValue;
    }

    FString FVerifyFormRequest::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    TOptional<FString> FVerifyFormRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyFormRequest> FVerifyFormRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyFormRequest>()
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
            ->WithMoldModelName(Data->HasField(ANSI_TO_TCHAR("moldModelName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("moldModelName"), v))
                  {
                        return TOptional(v);
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
            ->WithSlotName(Data->HasField(ANSI_TO_TCHAR("slotName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("slotName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPropertyIdRegex(Data->HasField(ANSI_TO_TCHAR("propertyIdRegex")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("propertyIdRegex"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCountType(Data->HasField(ANSI_TO_TCHAR("countType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("countType"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
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

    TSharedPtr<FJsonObject> FVerifyFormRequest::ToJson() const
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
        if (MoldModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("moldModelName"), MoldModelNameValue.GetValue());
        }
        if (IndexValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("index"), IndexValue.GetValue());
        }
        if (SlotNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("slotName"), SlotNameValue.GetValue());
        }
        if (PropertyIdRegexValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("propertyIdRegex"), PropertyIdRegexValue.GetValue());
        }
        if (CountTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("countType"), CountTypeValue.GetValue());
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