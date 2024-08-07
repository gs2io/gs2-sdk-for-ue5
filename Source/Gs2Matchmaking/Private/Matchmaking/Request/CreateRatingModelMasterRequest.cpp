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

#include "Matchmaking/Request/CreateRatingModelMasterRequest.h"

namespace Gs2::Matchmaking::Request
{
    FCreateRatingModelMasterRequest::FCreateRatingModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        InitialValueValue(TOptional<int32>()),
        VolatilityValue(TOptional<int32>())
    {
    }

    FCreateRatingModelMasterRequest::FCreateRatingModelMasterRequest(
        const FCreateRatingModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        InitialValueValue(From.InitialValueValue),
        VolatilityValue(From.VolatilityValue)
    {
    }

    TSharedPtr<FCreateRatingModelMasterRequest> FCreateRatingModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRatingModelMasterRequest> FCreateRatingModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRatingModelMasterRequest> FCreateRatingModelMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRatingModelMasterRequest> FCreateRatingModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRatingModelMasterRequest> FCreateRatingModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRatingModelMasterRequest> FCreateRatingModelMasterRequest::WithInitialValue(
        const TOptional<int32> InitialValue
    )
    {
        this->InitialValueValue = InitialValue;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRatingModelMasterRequest> FCreateRatingModelMasterRequest::WithVolatility(
        const TOptional<int32> Volatility
    )
    {
        this->VolatilityValue = Volatility;
        return SharedThis(this);
    }

    TOptional<FString> FCreateRatingModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateRatingModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateRatingModelMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateRatingModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateRatingModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int32> FCreateRatingModelMasterRequest::GetInitialValue() const
    {
        return InitialValueValue;
    }

    FString FCreateRatingModelMasterRequest::GetInitialValueString() const
    {
        if (!InitialValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialValueValue.GetValue());
    }

    TOptional<int32> FCreateRatingModelMasterRequest::GetVolatility() const
    {
        return VolatilityValue;
    }

    FString FCreateRatingModelMasterRequest::GetVolatilityString() const
    {
        if (!VolatilityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), VolatilityValue.GetValue());
    }

    TSharedPtr<FCreateRatingModelMasterRequest> FCreateRatingModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateRatingModelMasterRequest>()
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
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithInitialValue(Data->HasField(ANSI_TO_TCHAR("initialValue")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("initialValue"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithVolatility(Data->HasField(ANSI_TO_TCHAR("volatility")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("volatility"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FCreateRatingModelMasterRequest::ToJson() const
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
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (InitialValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("initialValue", InitialValueValue.GetValue());
        }
        if (VolatilityValue.IsSet())
        {
            JsonRootObject->SetNumberField("volatility", VolatilityValue.GetValue());
        }
        return JsonRootObject;
    }
}