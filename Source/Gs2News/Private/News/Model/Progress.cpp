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

#include "News/Model/Progress.h"

namespace Gs2::News::Model
{
    FProgress::FProgress():
        ProgressIdValue(TOptional<FString>()),
        UploadTokenValue(TOptional<FString>()),
        GeneratedValue(TOptional<int32>()),
        PatternCountValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FProgress::FProgress(
        const FProgress& From
    ):
        ProgressIdValue(From.ProgressIdValue),
        UploadTokenValue(From.UploadTokenValue),
        GeneratedValue(From.GeneratedValue),
        PatternCountValue(From.PatternCountValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FProgress> FProgress::WithProgressId(
        const TOptional<FString> ProgressId
    )
    {
        this->ProgressIdValue = ProgressId;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithUploadToken(
        const TOptional<FString> UploadToken
    )
    {
        this->UploadTokenValue = UploadToken;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithGenerated(
        const TOptional<int32> Generated
    )
    {
        this->GeneratedValue = Generated;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithPatternCount(
        const TOptional<int32> PatternCount
    )
    {
        this->PatternCountValue = PatternCount;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FProgress::GetProgressId() const
    {
        return ProgressIdValue;
    }
    TOptional<FString> FProgress::GetUploadToken() const
    {
        return UploadTokenValue;
    }
    TOptional<int32> FProgress::GetGenerated() const
    {
        return GeneratedValue;
    }

    FString FProgress::GetGeneratedString() const
    {
        if (!GeneratedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), GeneratedValue.GetValue());
    }
    TOptional<int32> FProgress::GetPatternCount() const
    {
        return PatternCountValue;
    }

    FString FProgress::GetPatternCountString() const
    {
        if (!PatternCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), PatternCountValue.GetValue());
    }
    TOptional<int64> FProgress::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FProgress::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FProgress::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FProgress::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FProgress::GetRevision() const
    {
        return RevisionValue;
    }

    FString FProgress::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FProgress::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):news:(?<namespaceName>.+):progress:(?<uploadToken>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FProgress::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):news:(?<namespaceName>.+):progress:(?<uploadToken>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FProgress::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):news:(?<namespaceName>.+):progress:(?<uploadToken>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FProgress::GetUploadTokenFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):news:(?<namespaceName>.+):progress:(?<uploadToken>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FProgress> FProgress::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FProgress>()
            ->WithProgressId(Data->HasField("progressId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("progressId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUploadToken(Data->HasField("uploadToken") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("uploadToken", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGenerated(Data->HasField("generated") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("generated", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithPatternCount(Data->HasField("patternCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("patternCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FProgress::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ProgressIdValue.IsSet())
        {
            JsonRootObject->SetStringField("progressId", ProgressIdValue.GetValue());
        }
        if (UploadTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("uploadToken", UploadTokenValue.GetValue());
        }
        if (GeneratedValue.IsSet())
        {
            JsonRootObject->SetNumberField("generated", GeneratedValue.GetValue());
        }
        if (PatternCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("patternCount", PatternCountValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FProgress::TypeName = "Progress";
}