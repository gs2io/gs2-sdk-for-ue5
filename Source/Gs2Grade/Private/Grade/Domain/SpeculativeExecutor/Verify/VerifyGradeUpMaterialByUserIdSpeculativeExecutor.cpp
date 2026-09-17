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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Grade/Domain/SpeculativeExecutor/Verify/VerifyGradeUpMaterialByUserIdSpeculativeExecutor.h"
#include "Grade/Domain/Gs2Grade.h"
#include "Grade/Model/Cache/GradeModel.h"
#include "Grade/Model/Cache/Status.h"
#include "Containers/Set.h"
#include "Internationalization/Regex.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Grade::Domain::SpeculativeExecutor
{
    namespace
    {
        using FStatusPtr = Gs2::Grade::Model::FStatusPtr;
        using FGradeModelPtr = Gs2::Grade::Model::FGradeModelPtr;

        bool GradeVerifyMaterialIsAscii(const FString& Value)
        {
            for (const TCHAR Character : Value)
            {
                if (Character > 0x7f) return false;
            }
            return true;
        }

        bool GradeVerifyMaterialPreparePattern(const FString& Pattern, FString& Prepared)
        {
            Prepared.Reset();
            TSet<FString> NamedGroups;
            bool InClass = false;
            bool ClassHasContent = false;
            TCHAR ClassPrevious = 0;
            bool ClassPreviousCanStartRange = false;
            int32 ClassRangeEndpoint = -1;
            int32 Parentheses = 0;
            int32 FiniteQuantifierCount = 0;
            bool HasNamedGroup = false;
            bool HasUnnamedCapture = false;
            for (int32 Index = 0; Index < Pattern.Len(); ++Index)
            {
                const TCHAR Character = Pattern[Index];
                if (Character > 0x7f) return false;
                if (Character == TEXT('\\'))
                {
                    if (InClass) return false;
                    if (Index + 1 >= Pattern.Len())
                    {
                        Prepared.AppendChar(Character);
                        continue;
                    }
                    TCHAR Escaped = Pattern[++Index];
                    const FString Allowed = TEXT("\\.^$|?*+()[]{}-afnrtvAz");
                    int32 AllowedIndex = INDEX_NONE;
                    if (Escaped > 0x7f || !Allowed.FindChar(Escaped, AllowedIndex)) return false;
                    Prepared.AppendChar(Character);
                    Prepared.AppendChar(Escaped);
                    continue;
                }
                if (Character == TEXT('['))
                {
                    if (InClass || (Index + 1 < Pattern.Len() && Pattern[Index + 1] == TEXT('['))) return false;
                    InClass = true;
                    ClassHasContent = false;
                    ClassPrevious = 0;
                    ClassPreviousCanStartRange = false;
                    ClassRangeEndpoint = -1;
                    Prepared.AppendChar(Character);
                    continue;
                }
                if (Character == TEXT(']') && InClass)
                {
                    if (!ClassHasContent) return false;
                    InClass = false;
                    Prepared.AppendChar(Character);
                    continue;
                }
                if (InClass)
                {
                    if (Character == TEXT('^') && !ClassHasContent)
                    {
                        Prepared.AppendChar(Character);
                        continue;
                    }
                    if (Character == TEXT('^')) return false;
                    if ((Character == TEXT('&') && Index + 1 < Pattern.Len() && Pattern[Index + 1] == TEXT('&')) ||
                        (Character == TEXT(':') && Index > 0 && Pattern[Index - 1] == TEXT('['))) return false;
                    if (Character == TEXT('-'))
                    {
                        const auto IsAlphaNumeric = [](const TCHAR Value) {
                            return (Value >= TEXT('0') && Value <= TEXT('9')) ||
                                (Value >= TEXT('a') && Value <= TEXT('z')) ||
                                (Value >= TEXT('A') && Value <= TEXT('Z'));
                        };
                        if (!ClassPreviousCanStartRange || Index + 1 >= Pattern.Len() ||
                            !IsAlphaNumeric(ClassPrevious) || !IsAlphaNumeric(Pattern[Index + 1]) ||
                            Pattern[Index + 1] < ClassPrevious) return false;
                        ClassRangeEndpoint = Index + 1;
                        ClassPreviousCanStartRange = false;
                        Prepared.AppendChar(Character);
                        continue;
                    }
                    ClassHasContent = true;
                    ClassPrevious = Character;
                    ClassPreviousCanStartRange = Index != ClassRangeEndpoint;
                    if (Index == ClassRangeEndpoint) ClassRangeEndpoint = -1;
                    Prepared.AppendChar(Character);
                    continue;
                }
                if (Character == TEXT('(') && Index + 1 < Pattern.Len() && Pattern[Index + 1] == TEXT('?'))
                {
                    if (Index + 2 < Pattern.Len() && Pattern[Index + 2] == TEXT(':'))
                    {
                        Prepared += TEXT("(?:");
                        Index += 2;
                        continue;
                    }
                    if (Index + 3 < Pattern.Len() && Pattern[Index + 2] == TEXT('P') && Pattern[Index + 3] == TEXT('<'))
                    {
                        int32 NameEnd = Index + 4;
                        while (NameEnd < Pattern.Len() &&
                            ((Pattern[NameEnd] >= TEXT('a') && Pattern[NameEnd] <= TEXT('z')) ||
                             (Pattern[NameEnd] >= TEXT('A') && Pattern[NameEnd] <= TEXT('Z')) ||
                             (Pattern[NameEnd] >= TEXT('0') && Pattern[NameEnd] <= TEXT('9')) ||
                             Pattern[NameEnd] == TEXT('_'))) ++NameEnd;
                        if (NameEnd == Index + 4 || NameEnd >= Pattern.Len() || Pattern[NameEnd] != TEXT('>')) return false;
                        const FString GroupName = Pattern.Mid(Index + 4, NameEnd - Index - 4);
                        if (!((GroupName[0] >= TEXT('a') && GroupName[0] <= TEXT('z')) ||
                              (GroupName[0] >= TEXT('A') && GroupName[0] <= TEXT('Z'))) || NamedGroups.Contains(GroupName)) return false;
                        NamedGroups.Add(GroupName);
                        HasNamedGroup = true;
                        Prepared += TEXT("(?<");
                        Prepared += GroupName;
                        Prepared += TEXT(">");
                        Index = NameEnd;
                        ++Parentheses;
                        continue;
                    }
                    return false;
                }
                if (Character == TEXT('('))
                {
                    ++Parentheses;
                    HasUnnamedCapture = true;
                }
                else if (Character == TEXT(')'))
                {
                    --Parentheses;
                }
                if (Character == TEXT('$'))
                {
                    Prepared += TEXT("\\z");
                    continue;
                }
                if (Character == TEXT('{'))
                {
                    ++FiniteQuantifierCount;
                    if (FiniteQuantifierCount > 1) return false;
                    int32 QuantifierEnd = Index + 1;
                    int32 DigitsBeforeComma = 0;
                    int32 LowerBound = 0;
                    while (QuantifierEnd < Pattern.Len() && Pattern[QuantifierEnd] >= TEXT('0') && Pattern[QuantifierEnd] <= TEXT('9'))
                    {
                        ++DigitsBeforeComma;
                        LowerBound = LowerBound > 1000 ? 1001 : LowerBound * 10 + Pattern[QuantifierEnd] - TEXT('0');
                        ++QuantifierEnd;
                    }
                    if (DigitsBeforeComma == 0 || LowerBound > 1000 || (DigitsBeforeComma > 1 && Pattern[Index + 1] == TEXT('0'))) return false;
                    if (QuantifierEnd < Pattern.Len() && Pattern[QuantifierEnd] == TEXT(','))
                    {
                        ++QuantifierEnd;
                        const int32 UpperBoundStart = QuantifierEnd;
                        int32 UpperBound = 0;
                        while (QuantifierEnd < Pattern.Len() && Pattern[QuantifierEnd] >= TEXT('0') && Pattern[QuantifierEnd] <= TEXT('9'))
                        {
                            UpperBound = UpperBound > 1000 ? 1001 : UpperBound * 10 + Pattern[QuantifierEnd] - TEXT('0');
                            ++QuantifierEnd;
                        }
                        if (UpperBound > 1000 || (QuantifierEnd - UpperBoundStart > 1 && Pattern[UpperBoundStart] == TEXT('0'))) return false;
                    }
                    if (QuantifierEnd >= Pattern.Len() || Pattern[QuantifierEnd] != TEXT('}')) return false;
                    Prepared += Pattern.Mid(Index, QuantifierEnd - Index + 1);
                    Index = QuantifierEnd;
                    continue;
                }
                Prepared.AppendChar(Character);
            }
            if (InClass) return true;
            if (HasNamedGroup && HasUnnamedCapture) return false;
            return true;
        }

        FString GradeVerifyMaterialPortablePattern(FString Pattern)
        {
            Pattern.ReplaceInline(TEXT("(?P<"), TEXT("(?<"));
            return Pattern;
        }

        void GradeVerifyMaterialCaptureNames(const FString& Pattern, TArray<FString>& Names)
        {
            Names.Reset();
            bool InCharacterClass = false;
            for (int32 Index = 0; Index < Pattern.Len(); ++Index)
            {
                if (Pattern[Index] == TEXT('\\'))
                {
                    int32 SlashCount = 1;
                    while (Index + SlashCount < Pattern.Len() && Pattern[Index + SlashCount] == TEXT('\\')) ++SlashCount;
                    if ((SlashCount & 1) != 0 && Index + SlashCount < Pattern.Len()) ++SlashCount;
                    Index += SlashCount - 1;
                    continue;
                }
                if (Pattern[Index] == TEXT('['))
                {
                    InCharacterClass = true;
                    continue;
                }
                if (Pattern[Index] == TEXT(']'))
                {
                    InCharacterClass = false;
                    continue;
                }
                if (InCharacterClass) continue;
                if (Pattern[Index] != TEXT('(')) continue;
                if (Index + 2 < Pattern.Len() && Pattern[Index + 1] == TEXT('?') && Pattern[Index + 2] == TEXT('<'))
                {
                    int32 End = Index + 3;
                    while (End < Pattern.Len() && Pattern[End] != TEXT('>')) ++End;
                    Names.Add(End < Pattern.Len() ? Pattern.Mid(Index + 3, End - Index - 3) : FString());
                    continue;
                }
                if (Index + 1 >= Pattern.Len() || Pattern[Index + 1] != TEXT('?')) Names.Add(FString());
            }
        }

        FString GradeVerifyMaterialExpandReplacement(
            const FString& Replacement,
            FRegexMatcher& Matcher,
            const TArray<FString>& CaptureNames
        )
        {
            FString Expanded;
            for (int32 Index = 0; Index < Replacement.Len(); ++Index)
            {
                if (Replacement[Index] != TEXT('$'))
                {
                    Expanded.AppendChar(Replacement[Index]);
                    continue;
                }
                if (Index + 1 < Replacement.Len() && Replacement[Index + 1] == TEXT('$'))
                {
                    Expanded.AppendChar(TEXT('$'));
                    ++Index;
                    continue;
                }
                int32 NameStart = Index + 1;
                const bool Braced = NameStart < Replacement.Len() && Replacement[NameStart] == TEXT('{');
                if (Braced) ++NameStart;
                int32 End = NameStart;
                while (End < Replacement.Len() &&
                    ((Replacement[End] >= TEXT('0') && Replacement[End] <= TEXT('9')) ||
                     (Replacement[End] >= TEXT('A') && Replacement[End] <= TEXT('Z')) ||
                     (Replacement[End] >= TEXT('a') && Replacement[End] <= TEXT('z')) ||
                     Replacement[End] == TEXT('_'))) ++End;
                if (End == NameStart || (Braced && (End >= Replacement.Len() || Replacement[End] != TEXT('}'))))
                {
                    Expanded.AppendChar(TEXT('$'));
                    continue;
                }
                const FString Name = Replacement.Mid(NameStart, End - NameStart);
                int32 Group = -1;
                bool Numeric = true;
                int32 ParsedNumber = 0;
                for (const TCHAR Character : Name)
                {
                    if (Character < TEXT('0') || Character > TEXT('9') || ParsedNumber >= 100000000) { Numeric = false; break; }
                    ParsedNumber = ParsedNumber * 10 + Character - TEXT('0');
                }
                if (Numeric && !(Name.Len() > 1 && Name[0] == TEXT('0'))) Group = ParsedNumber;
                else
                {
                    for (int32 NameIndex = 0; NameIndex < CaptureNames.Num(); ++NameIndex)
                    {
                        if (CaptureNames[NameIndex] == Name) { Group = NameIndex + 1; break; }
                    }
                }
                if (Group >= 0) Expanded += Matcher.GetCaptureGroup(Group);
                Index = End + (Braced ? 1 : 0) - 1;
            }
            return Expanded;
        }

        bool GradeVerifyMaterialReplaceAll(
            const FString& Pattern,
            const FString& Source,
            const FString& Replacement,
            FString& Output,
            bool& ConstructionFailed
        )
        {
            ConstructionFailed = false;
            if (!GradeVerifyMaterialIsAscii(Pattern) || !GradeVerifyMaterialIsAscii(Source) || !GradeVerifyMaterialIsAscii(Replacement)) return false;
            int32 Parentheses = 0;
            bool InClass = false;
            for (int32 Index = 0; Index < Pattern.Len(); ++Index)
            {
                if (Pattern[Index] == TEXT('\\'))
                {
                    if (Index + 1 >= Pattern.Len()) { ConstructionFailed = true; return false; }
                    ++Index;
                    continue;
                }
                if (Pattern[Index] == TEXT('[')) InClass = true;
                else if (Pattern[Index] == TEXT(']')) InClass = false;
                else if (!InClass && Pattern[Index] == TEXT('(')) ++Parentheses;
                else if (!InClass && Pattern[Index] == TEXT(')')) --Parentheses;
                if (Parentheses < 0) { ConstructionFailed = true; return false; }
            }
            if (InClass || Parentheses != 0) { ConstructionFailed = true; return false; }
            FString PreparedPattern;
            if (!GradeVerifyMaterialPreparePattern(Pattern, PreparedPattern)) return false;
            PreparedPattern = GradeVerifyMaterialPortablePattern(PreparedPattern);
            const FRegexPattern RegexPattern(PreparedPattern);
            FRegexMatcher Matcher(RegexPattern, Source);
            TArray<FString> CaptureNames;
            GradeVerifyMaterialCaptureNames(PreparedPattern, CaptureNames);
            Output.Reset();
            int32 LastEnd = 0;
            while (Matcher.FindNext())
            {
                const int32 Begin = Matcher.GetMatchBeginning();
                const int32 End = Matcher.GetMatchEnding();
                if (Begin < LastEnd || End < Begin) return false;
                Output += Source.Mid(LastEnd, Begin - LastEnd);
                Output += GradeVerifyMaterialExpandReplacement(Replacement, Matcher, CaptureNames);
                LastEnd = End;
            }
            Output += Source.Mid(LastEnd);
            return true;
        }

        bool GradeVerifyMaterialEvaluate(
            const FStatusPtr& Status,
            const Gs2::Grade::Request::FVerifyGradeUpMaterialByUserIdRequestPtr& Request,
            const FGradeModelPtr& GradeModel,
            const FString& Region,
            const FString& OwnerId,
            const FString& UserId,
            bool& Matches
        )
        {
            Matches = false;
            if (!Status.IsValid() || !Status->GetGradeValue().IsSet() || *Status->GetGradeValue() <= 0 ||
                !Request.IsValid() || !Request->GetPropertyId().IsSet() || Request->GetPropertyId().Get(FString()).IsEmpty() ||
                !Request->GetMaterialPropertyId().IsSet() || Request->GetMaterialPropertyId().Get(FString()).IsEmpty() ||
                !GradeModel.IsValid() || !GradeModel->GetGradeEntries().IsValid() || GradeModel->GetGradeEntries()->Num() == 0) return false;
            if (!GradeVerifyMaterialIsAscii(Request->GetPropertyId().Get(FString())) ||
                !GradeVerifyMaterialIsAscii(Request->GetMaterialPropertyId().Get(FString()))) return false;
            const int32 EntryIndex = FMath::Min<int64>(GradeModel->GetGradeEntries()->Num() - 1, *Status->GetGradeValue() - 1);
            const auto Entry = (*GradeModel->GetGradeEntries())[EntryIndex];
            if (!Entry.IsValid() || !Entry->GetPropertyIdRegex().IsSet() || Entry->GetPropertyIdRegex().Get(FString()).IsEmpty() ||
                !Entry->GetGradeUpPropertyIdRegex().IsSet() || Entry->GetGradeUpPropertyIdRegex().Get(FString()).IsEmpty()) return false;
            FString PropertyPattern = *Entry->GetPropertyIdRegex();
            FString MaterialPattern = *Entry->GetGradeUpPropertyIdRegex();
            PropertyPattern.ReplaceInline(TEXT("{region}"), *Region);
            PropertyPattern.ReplaceInline(TEXT("{ownerId}"), *OwnerId);
            PropertyPattern.ReplaceInline(TEXT("{userId}"), *UserId);
            MaterialPattern.ReplaceInline(TEXT("{region}"), *Region);
            MaterialPattern.ReplaceInline(TEXT("{ownerId}"), *OwnerId);
            MaterialPattern.ReplaceInline(TEXT("{userId}"), *UserId);
            FString MaterialPropertyPattern;
            bool PropertyRegexConstructionFailed = false;
            if (!GradeVerifyMaterialReplaceAll(PropertyPattern, Request->GetPropertyId().Get(FString()), MaterialPattern,
                MaterialPropertyPattern, PropertyRegexConstructionFailed))
            {
                if (!PropertyRegexConstructionFailed) return false;
                MaterialPropertyPattern = Request->GetPropertyId().Get(FString());
            }
            if (!GradeVerifyMaterialIsAscii(MaterialPropertyPattern)) return false;
            FString PreparedMaterialPattern;
            if (!GradeVerifyMaterialPreparePattern(MaterialPropertyPattern, PreparedMaterialPattern)) return false;
            const FRegexPattern MaterialRegex(GradeVerifyMaterialPortablePattern(PreparedMaterialPattern));
            FRegexMatcher MaterialMatcher(MaterialRegex, Request->GetMaterialPropertyId().Get(FString()));
            Matches = MaterialMatcher.FindNext();
            return true;
        }

        Gs2::Core::Model::FGs2ErrorPtr GradeVerifyMaterialFailure()
        {
            const auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("materialPropertyId"), TEXT("invalid"), TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
    }

    FString FVerifyGradeUpMaterialByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Grade:VerifyGradeUpMaterialByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyGradeUpMaterialByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FVerifyGradeUpMaterialByUserIdRequestPtr& Request,
        Gs2::Grade::Model::FStatusPtr Item,
        Gs2::Grade::Model::FGradeModelPtr GradeModel,
        const FString& Region,
        const FString& OwnerId,
        const FString& UserId
    )
    {
        if (!Request.IsValid() || !Request->GetVerifyType().IsSet() ||
            (*Request->GetVerifyType() != TEXT("match") && *Request->GetVerifyType() != TEXT("notMatch")))
        {
            const auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("verifyType"), TEXT("invalid"), TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        bool Matches = false;
        if (!GradeVerifyMaterialEvaluate(Item, Request, GradeModel, Region, OwnerId, UserId, Matches)) return GradeVerifyMaterialFailure();
        const bool Executable = Request->GetVerifyType().Get(FString()) == TEXT("match") ? Matches : !Matches;
        if (!Executable) return GradeVerifyMaterialFailure();
        return nullptr;
    }

    FVerifyGradeUpMaterialByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FVerifyGradeUpMaterialByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyGradeUpMaterialByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyGradeUpMaterialByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !AccessToken.IsValid() || !Request.IsValid()) return nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        const auto PreparedRequest = Gs2::Grade::Request::FVerifyGradeUpMaterialByUserIdRequest::FromJson(Request->ToJson());
        if (!PreparedToken.IsValid() || !PreparedRequest.IsValid() || !PreparedToken->GetUserId().IsSet() ||
            PreparedToken->GetUserId().Get(FString()).IsEmpty() || Domain->RestSession->OwnerId().IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && *PreparedRequest->GetUserId() == TEXT("#{userId}"))
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
            !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetGradeName().IsSet() || PreparedRequest->GetGradeName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetPropertyId().IsSet() || PreparedRequest->GetPropertyId().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetMaterialPropertyId().IsSet() || PreparedRequest->GetMaterialPropertyId().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetVerifyType().IsSet() ||
            (*PreparedRequest->GetVerifyType() != TEXT("match") && *PreparedRequest->GetVerifyType() != TEXT("notMatch"))) return nullptr;
        const FString Region = Domain->RestSession->RegionName();
        const FString OwnerId = Domain->RestSession->OwnerId();
        const FString UserId = PreparedToken->GetUserId().Get(FString());
        FString PropertyId = PreparedRequest->GetPropertyId().Get(FString());
        PropertyId.ReplaceInline(TEXT("{region}"), *Region);
        PropertyId.ReplaceInline(TEXT("{ownerId}"), *OwnerId);
        PropertyId.ReplaceInline(TEXT("{userId}"), *UserId);
        PreparedRequest->WithPropertyId(PropertyId);
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const FString GradeName = PreparedRequest->GetGradeName().Get(FString());
        const FString ExpectedStatusId = FString::Printf(
            TEXT("grn:gs2:%s:%s:grade:%s:user:%s:gradeModel:%s:property:%s"), *Region, *OwnerId,
            *NamespaceName.Get(FString()), *UserId, *GradeName, *PropertyId);
        const FString ExpectedGradeModelId = FString::Printf(
            TEXT("grn:gs2:%s:%s:grade:%s:model:%s"), *Region, *OwnerId, *NamespaceName.Get(FString()), *GradeName);
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        FStatusPtr Item;
        FGradeModelPtr GradeModel;
        if (!Gs2::Grade::Model::Cache::FStatusCache::TryGet(Domain->Cache, NamespaceName, UserId, GradeName, PropertyId, TimeOffset, &Item) ||
            !Gs2::Grade::Model::Cache::FGradeModelCache::TryGet(Domain->Cache, NamespaceName, GradeName, TOptional<int32>(), &GradeModel) ||
            !Item.IsValid() || !GradeModel.IsValid() || !Item->GetStatusId().IsSet() || *Item->GetStatusId() != ExpectedStatusId ||
            !Item->GetUserId().IsSet() || *Item->GetUserId() != UserId || !Item->GetGradeName().IsSet() || *Item->GetGradeName() != GradeName ||
            !Item->GetPropertyId().IsSet() || *Item->GetPropertyId() != PropertyId || !GradeModel->GetGradeModelId().IsSet() ||
            *GradeModel->GetGradeModelId() != ExpectedGradeModelId || !GradeModel->GetName().IsSet() || *GradeModel->GetName() != GradeName) return nullptr;
        if (const auto Error = Transform(Domain, PreparedToken, PreparedRequest, Item, GradeModel, Region, OwnerId, UserId); Error.IsValid()) return Error;
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, GradeName, PropertyId, TimeOffset, ExpectedStatusId,
            ExpectedGradeModelId, Region, OwnerId, PreparedRequest, VerifyType]()
        {
            FStatusPtr Current;
            FGradeModelPtr CurrentModel;
            if (!Gs2::Grade::Model::Cache::FStatusCache::TryGet(Cache, NamespaceName, UserId, GradeName, PropertyId, TimeOffset, &Current) ||
                !Gs2::Grade::Model::Cache::FGradeModelCache::TryGet(Cache, NamespaceName, GradeName, TOptional<int32>(), &CurrentModel) ||
                !Current.IsValid() || !CurrentModel.IsValid() || !Current->GetStatusId().IsSet() || *Current->GetStatusId() != ExpectedStatusId ||
                !Current->GetUserId().IsSet() || *Current->GetUserId() != UserId ||
                !Current->GetGradeName().IsSet() || *Current->GetGradeName() != GradeName ||
                !Current->GetPropertyId().IsSet() || *Current->GetPropertyId() != PropertyId ||
                !CurrentModel->GetGradeModelId().IsSet() || *CurrentModel->GetGradeModelId() != ExpectedGradeModelId ||
                !CurrentModel->GetName().IsSet() || *CurrentModel->GetName() != GradeName) return false;
            bool Matches = false;
            if (!GradeVerifyMaterialEvaluate(Current, PreparedRequest, CurrentModel, Region, OwnerId, UserId, Matches)) return false;
            return Matches == (VerifyType == TEXT("match"));
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyGradeUpMaterialByUserIdSpeculativeExecutor::FCommitTask>> FVerifyGradeUpMaterialByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FVerifyGradeUpMaterialByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyGradeUpMaterialByUserIdSpeculativeExecutor::FCommitTask>> FVerifyGradeUpMaterialByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FVerifyGradeUpMaterialByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Grade::Request::FVerifyGradeUpMaterialByUserIdRequest::FromJson(Request->ToJson());
        if (!Inverse.IsValid() || !Inverse->GetVerifyType().IsSet()) return nullptr;
        if (*Inverse->GetVerifyType() == TEXT("match")) Inverse->WithVerifyType(TOptional<FString>(TEXT("notMatch")));
        else if (*Inverse->GetVerifyType() == TEXT("notMatch")) Inverse->WithVerifyType(TOptional<FString>(TEXT("match")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Grade::Request::FVerifyGradeUpMaterialByUserIdRequestPtr FVerifyGradeUpMaterialByUserIdSpeculativeExecutor::Rate(
        const Gs2::Grade::Request::FVerifyGradeUpMaterialByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Grade::Request::FVerifyGradeUpMaterialByUserIdRequestPtr FVerifyGradeUpMaterialByUserIdSpeculativeExecutor::Rate(
        const Gs2::Grade::Request::FVerifyGradeUpMaterialByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
