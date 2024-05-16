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

#include "Grade/Request/DeleteGradeModelMasterRequest.h"

namespace Gs2::Grade::Request
{
    FDeleteGradeModelMasterRequest::FDeleteGradeModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        GradeNameValue(TOptional<FString>())
    {
    }

    FDeleteGradeModelMasterRequest::FDeleteGradeModelMasterRequest(
        const FDeleteGradeModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        GradeNameValue(From.GradeNameValue)
    {
    }

    TSharedPtr<FDeleteGradeModelMasterRequest> FDeleteGradeModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteGradeModelMasterRequest> FDeleteGradeModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteGradeModelMasterRequest> FDeleteGradeModelMasterRequest::WithGradeName(
        const TOptional<FString> GradeName
    )
    {
        this->GradeNameValue = GradeName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteGradeModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteGradeModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteGradeModelMasterRequest::GetGradeName() const
    {
        return GradeNameValue;
    }

    TSharedPtr<FDeleteGradeModelMasterRequest> FDeleteGradeModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteGradeModelMasterRequest>()
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
            ->WithGradeName(Data->HasField(ANSI_TO_TCHAR("gradeName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("gradeName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteGradeModelMasterRequest::ToJson() const
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
        if (GradeNameValue.IsSet())
        {
            JsonRootObject->SetStringField("gradeName", GradeNameValue.GetValue());
        }
        return JsonRootObject;
    }
}