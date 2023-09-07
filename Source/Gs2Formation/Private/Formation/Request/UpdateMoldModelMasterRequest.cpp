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

#include "Formation/Request/UpdateMoldModelMasterRequest.h"

namespace Gs2::Formation::Request
{
    FUpdateMoldModelMasterRequest::FUpdateMoldModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        MoldModelNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        FormModelNameValue(TOptional<FString>()),
        InitialMaxCapacityValue(TOptional<int32>()),
        MaxCapacityValue(TOptional<int32>())
    {
    }

    FUpdateMoldModelMasterRequest::FUpdateMoldModelMasterRequest(
        const FUpdateMoldModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        MoldModelNameValue(From.MoldModelNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        FormModelNameValue(From.FormModelNameValue),
        InitialMaxCapacityValue(From.InitialMaxCapacityValue),
        MaxCapacityValue(From.MaxCapacityValue)
    {
    }

    TSharedPtr<FUpdateMoldModelMasterRequest> FUpdateMoldModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMoldModelMasterRequest> FUpdateMoldModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMoldModelMasterRequest> FUpdateMoldModelMasterRequest::WithMoldModelName(
        const TOptional<FString> MoldModelName
    )
    {
        this->MoldModelNameValue = MoldModelName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMoldModelMasterRequest> FUpdateMoldModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMoldModelMasterRequest> FUpdateMoldModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMoldModelMasterRequest> FUpdateMoldModelMasterRequest::WithFormModelName(
        const TOptional<FString> FormModelName
    )
    {
        this->FormModelNameValue = FormModelName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMoldModelMasterRequest> FUpdateMoldModelMasterRequest::WithInitialMaxCapacity(
        const TOptional<int32> InitialMaxCapacity
    )
    {
        this->InitialMaxCapacityValue = InitialMaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMoldModelMasterRequest> FUpdateMoldModelMasterRequest::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateMoldModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateMoldModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateMoldModelMasterRequest::GetMoldModelName() const
    {
        return MoldModelNameValue;
    }

    TOptional<FString> FUpdateMoldModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateMoldModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateMoldModelMasterRequest::GetFormModelName() const
    {
        return FormModelNameValue;
    }

    TOptional<int32> FUpdateMoldModelMasterRequest::GetInitialMaxCapacity() const
    {
        return InitialMaxCapacityValue;
    }

    FString FUpdateMoldModelMasterRequest::GetInitialMaxCapacityString() const
    {
        if (!InitialMaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialMaxCapacityValue.GetValue());
    }

    TOptional<int32> FUpdateMoldModelMasterRequest::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FUpdateMoldModelMasterRequest::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxCapacityValue.GetValue());
    }

    TSharedPtr<FUpdateMoldModelMasterRequest> FUpdateMoldModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateMoldModelMasterRequest>()
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
            ->WithMoldModelName(Data->HasField("moldModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("moldModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithFormModelName(Data->HasField("formModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("formModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithInitialMaxCapacity(Data->HasField("initialMaxCapacity") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("initialMaxCapacity", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithMaxCapacity(Data->HasField("maxCapacity") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("maxCapacity", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FUpdateMoldModelMasterRequest::ToJson() const
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
        if (MoldModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("moldModelName", MoldModelNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (FormModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("formModelName", FormModelNameValue.GetValue());
        }
        if (InitialMaxCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("initialMaxCapacity", InitialMaxCapacityValue.GetValue());
        }
        if (MaxCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxCapacity", MaxCapacityValue.GetValue());
        }
        return JsonRootObject;
    }
}