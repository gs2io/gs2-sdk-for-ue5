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

#include "Distributor/Request/BatchExecuteApiRequest.h"

namespace Gs2::Distributor::Request
{
    FBatchExecuteApiRequest::FBatchExecuteApiRequest():
        RequestPayloadsValue(nullptr)
    {
    }

    FBatchExecuteApiRequest::FBatchExecuteApiRequest(
        const FBatchExecuteApiRequest& From
    ):
        RequestPayloadsValue(From.RequestPayloadsValue)
    {
    }

    TSharedPtr<FBatchExecuteApiRequest> FBatchExecuteApiRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FBatchExecuteApiRequest> FBatchExecuteApiRequest::WithRequestPayloads(
        const TSharedPtr<TArray<TSharedPtr<Model::FBatchRequestPayload>>> RequestPayloads
    )
    {
        this->RequestPayloadsValue = RequestPayloads;
        return SharedThis(this);
    }

    TOptional<FString> FBatchExecuteApiRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FBatchRequestPayload>>> FBatchExecuteApiRequest::GetRequestPayloads() const
    {
        if (!RequestPayloadsValue.IsValid())
        {
            return nullptr;
        }
        return RequestPayloadsValue;
    }

    TSharedPtr<FBatchExecuteApiRequest> FBatchExecuteApiRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBatchExecuteApiRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
          ->WithRequestPayloads(Data->HasField(ANSI_TO_TCHAR("requestPayloads")) ? [Data]() -> TSharedPtr<TArray<Model::FBatchRequestPayloadPtr>>
              {
                  auto v = MakeShared<TArray<Model::FBatchRequestPayloadPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("requestPayloads")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("requestPayloads")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("requestPayloads")))
                      {
                          v->Add(Model::FBatchRequestPayload::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FBatchRequestPayloadPtr>>());
    }

    TSharedPtr<FJsonObject> FBatchExecuteApiRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (RequestPayloadsValue != nullptr && RequestPayloadsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RequestPayloadsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("requestPayloads", v);
        }
        return JsonRootObject;
    }
}