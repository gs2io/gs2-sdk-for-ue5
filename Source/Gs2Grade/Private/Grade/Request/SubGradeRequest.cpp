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

#include "Grade/Request/SubGradeRequest.h"

namespace Gs2::Grade::Request
{
    FSubGradeRequest::FSubGradeRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        GradeNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        GradeValueValue(TOptional<int64>())
    {
    }

    FSubGradeRequest::FSubGradeRequest(
        const FSubGradeRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        GradeNameValue(From.GradeNameValue),
        PropertyIdValue(From.PropertyIdValue),
        GradeValueValue(From.GradeValueValue)
    {
    }

    TSharedPtr<FSubGradeRequest> FSubGradeRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSubGradeRequest> FSubGradeRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSubGradeRequest> FSubGradeRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FSubGradeRequest> FSubGradeRequest::WithGradeName(
        const TOptional<FString> GradeName
    )
    {
        this->GradeNameValue = GradeName;
        return SharedThis(this);
    }

    TSharedPtr<FSubGradeRequest> FSubGradeRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FSubGradeRequest> FSubGradeRequest::WithGradeValue(
        const TOptional<int64> GradeValue
    )
    {
        this->GradeValueValue = GradeValue;
        return SharedThis(this);
    }

    TSharedPtr<FSubGradeRequest> FSubGradeRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSubGradeRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSubGradeRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSubGradeRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FSubGradeRequest::GetGradeName() const
    {
        return GradeNameValue;
    }

    TOptional<FString> FSubGradeRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TOptional<int64> FSubGradeRequest::GetGradeValue() const
    {
        return GradeValueValue;
    }

    FString FSubGradeRequest::GetGradeValueString() const
    {
        if (!GradeValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), GradeValueValue.GetValue());
    }

    TOptional<FString> FSubGradeRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSubGradeRequest> FSubGradeRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSubGradeRequest>()
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
            ->WithGradeName(Data->HasField(ANSI_TO_TCHAR("gradeName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("gradeName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPropertyId(Data->HasField(ANSI_TO_TCHAR("propertyId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("propertyId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithGradeValue(Data->HasField(ANSI_TO_TCHAR("gradeValue")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("gradeValue"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSubGradeRequest::ToJson() const
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
        if (GradeNameValue.IsSet())
        {
            JsonRootObject->SetStringField("gradeName", GradeNameValue.GetValue());
        }
        if (PropertyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyId", PropertyIdValue.GetValue());
        }
        if (GradeValueValue.IsSet())
        {
            JsonRootObject->SetStringField("gradeValue", FString::Printf(TEXT("%lld"), GradeValueValue.GetValue()));
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}