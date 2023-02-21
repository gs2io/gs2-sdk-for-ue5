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

#include "Datastore/Model/DataObjectHistory.h"

namespace Gs2::Datastore::Model
{
    FDataObjectHistory::FDataObjectHistory():
        DataObjectHistoryIdValue(TOptional<FString>()),
        DataObjectNameValue(TOptional<FString>()),
        GenerationValue(TOptional<FString>()),
        ContentLengthValue(TOptional<int64>()),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FDataObjectHistory::FDataObjectHistory(
        const FDataObjectHistory& From
    ):
        DataObjectHistoryIdValue(From.DataObjectHistoryIdValue),
        DataObjectNameValue(From.DataObjectNameValue),
        GenerationValue(From.GenerationValue),
        ContentLengthValue(From.ContentLengthValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FDataObjectHistory> FDataObjectHistory::WithDataObjectHistoryId(
        const TOptional<FString> DataObjectHistoryId
    )
    {
        this->DataObjectHistoryIdValue = DataObjectHistoryId;
        return SharedThis(this);
    }

    TSharedPtr<FDataObjectHistory> FDataObjectHistory::WithDataObjectName(
        const TOptional<FString> DataObjectName
    )
    {
        this->DataObjectNameValue = DataObjectName;
        return SharedThis(this);
    }

    TSharedPtr<FDataObjectHistory> FDataObjectHistory::WithGeneration(
        const TOptional<FString> Generation
    )
    {
        this->GenerationValue = Generation;
        return SharedThis(this);
    }

    TSharedPtr<FDataObjectHistory> FDataObjectHistory::WithContentLength(
        const TOptional<int64> ContentLength
    )
    {
        this->ContentLengthValue = ContentLength;
        return SharedThis(this);
    }

    TSharedPtr<FDataObjectHistory> FDataObjectHistory::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FDataObjectHistory::GetDataObjectHistoryId() const
    {
        return DataObjectHistoryIdValue;
    }
    TOptional<FString> FDataObjectHistory::GetDataObjectName() const
    {
        return DataObjectNameValue;
    }
    TOptional<FString> FDataObjectHistory::GetGeneration() const
    {
        return GenerationValue;
    }
    TOptional<int64> FDataObjectHistory::GetContentLength() const
    {
        return ContentLengthValue;
    }

    FString FDataObjectHistory::GetContentLengthString() const
    {
        if (!ContentLengthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ContentLengthValue.GetValue());
    }
    TOptional<int64> FDataObjectHistory::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FDataObjectHistory::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TOptional<FString> FDataObjectHistory::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):datastore:(?<namespaceName>.+):user:(?<userId>.+):data:(?<dataObjectName>.+):history:(?<generation>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDataObjectHistory::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):datastore:(?<namespaceName>.+):user:(?<userId>.+):data:(?<dataObjectName>.+):history:(?<generation>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDataObjectHistory::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):datastore:(?<namespaceName>.+):user:(?<userId>.+):data:(?<dataObjectName>.+):history:(?<generation>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDataObjectHistory::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):datastore:(?<namespaceName>.+):user:(?<userId>.+):data:(?<dataObjectName>.+):history:(?<generation>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDataObjectHistory::GetDataObjectNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):datastore:(?<namespaceName>.+):user:(?<userId>.+):data:(?<dataObjectName>.+):history:(?<generation>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDataObjectHistory::GetGenerationFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):datastore:(?<namespaceName>.+):user:(?<userId>.+):data:(?<dataObjectName>.+):history:(?<generation>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FDataObjectHistory> FDataObjectHistory::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDataObjectHistory>()
            ->WithDataObjectHistoryId(Data->HasField("dataObjectHistoryId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("dataObjectHistoryId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDataObjectName(Data->HasField("dataObjectName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("dataObjectName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGeneration(Data->HasField("generation") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("generation", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithContentLength(Data->HasField("contentLength") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("contentLength", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FDataObjectHistory::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DataObjectHistoryIdValue.IsSet())
        {
            JsonRootObject->SetStringField("dataObjectHistoryId", DataObjectHistoryIdValue.GetValue());
        }
        if (DataObjectNameValue.IsSet())
        {
            JsonRootObject->SetStringField("dataObjectName", DataObjectNameValue.GetValue());
        }
        if (GenerationValue.IsSet())
        {
            JsonRootObject->SetStringField("generation", GenerationValue.GetValue());
        }
        if (ContentLengthValue.IsSet())
        {
            JsonRootObject->SetStringField("contentLength", FString::Printf(TEXT("%lld"), ContentLengthValue.GetValue()));
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FDataObjectHistory::TypeName = "DataObjectHistory";
}