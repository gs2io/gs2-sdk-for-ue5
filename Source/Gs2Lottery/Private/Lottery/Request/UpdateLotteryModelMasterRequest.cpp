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

#include "Lottery/Request/UpdateLotteryModelMasterRequest.h"

namespace Gs2::Lottery::Request
{
    FUpdateLotteryModelMasterRequest::FUpdateLotteryModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        LotteryNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ModeValue(TOptional<FString>()),
        MethodValue(TOptional<FString>()),
        PrizeTableNameValue(TOptional<FString>()),
        ChoicePrizeTableScriptIdValue(TOptional<FString>())
    {
    }

    FUpdateLotteryModelMasterRequest::FUpdateLotteryModelMasterRequest(
        const FUpdateLotteryModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        LotteryNameValue(From.LotteryNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ModeValue(From.ModeValue),
        MethodValue(From.MethodValue),
        PrizeTableNameValue(From.PrizeTableNameValue),
        ChoicePrizeTableScriptIdValue(From.ChoicePrizeTableScriptIdValue)
    {
    }

    TSharedPtr<FUpdateLotteryModelMasterRequest> FUpdateLotteryModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLotteryModelMasterRequest> FUpdateLotteryModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLotteryModelMasterRequest> FUpdateLotteryModelMasterRequest::WithLotteryName(
        const TOptional<FString> LotteryName
    )
    {
        this->LotteryNameValue = LotteryName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLotteryModelMasterRequest> FUpdateLotteryModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLotteryModelMasterRequest> FUpdateLotteryModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLotteryModelMasterRequest> FUpdateLotteryModelMasterRequest::WithMode(
        const TOptional<FString> Mode
    )
    {
        this->ModeValue = Mode;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLotteryModelMasterRequest> FUpdateLotteryModelMasterRequest::WithMethod(
        const TOptional<FString> Method
    )
    {
        this->MethodValue = Method;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLotteryModelMasterRequest> FUpdateLotteryModelMasterRequest::WithPrizeTableName(
        const TOptional<FString> PrizeTableName
    )
    {
        this->PrizeTableNameValue = PrizeTableName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLotteryModelMasterRequest> FUpdateLotteryModelMasterRequest::WithChoicePrizeTableScriptId(
        const TOptional<FString> ChoicePrizeTableScriptId
    )
    {
        this->ChoicePrizeTableScriptIdValue = ChoicePrizeTableScriptId;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateLotteryModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateLotteryModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateLotteryModelMasterRequest::GetLotteryName() const
    {
        return LotteryNameValue;
    }

    TOptional<FString> FUpdateLotteryModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateLotteryModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateLotteryModelMasterRequest::GetMode() const
    {
        return ModeValue;
    }

    TOptional<FString> FUpdateLotteryModelMasterRequest::GetMethod() const
    {
        return MethodValue;
    }

    TOptional<FString> FUpdateLotteryModelMasterRequest::GetPrizeTableName() const
    {
        return PrizeTableNameValue;
    }

    TOptional<FString> FUpdateLotteryModelMasterRequest::GetChoicePrizeTableScriptId() const
    {
        return ChoicePrizeTableScriptIdValue;
    }

    TSharedPtr<FUpdateLotteryModelMasterRequest> FUpdateLotteryModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateLotteryModelMasterRequest>()
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
            ->WithLotteryName(Data->HasField("lotteryName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("lotteryName", v))
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
            ->WithMode(Data->HasField("mode") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("mode", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMethod(Data->HasField("method") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("method", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPrizeTableName(Data->HasField("prizeTableName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("prizeTableName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithChoicePrizeTableScriptId(Data->HasField("choicePrizeTableScriptId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("choicePrizeTableScriptId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateLotteryModelMasterRequest::ToJson() const
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
        if (LotteryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("lotteryName", LotteryNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ModeValue.IsSet())
        {
            JsonRootObject->SetStringField("mode", ModeValue.GetValue());
        }
        if (MethodValue.IsSet())
        {
            JsonRootObject->SetStringField("method", MethodValue.GetValue());
        }
        if (PrizeTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeTableName", PrizeTableNameValue.GetValue());
        }
        if (ChoicePrizeTableScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("choicePrizeTableScriptId", ChoicePrizeTableScriptIdValue.GetValue());
        }
        return JsonRootObject;
    }
}